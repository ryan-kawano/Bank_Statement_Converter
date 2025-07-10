/**
 * @file pdf_processor.cpp
 * @brief Source file for the PdfProcessor class.
 */
#include <fstream>
#include <filesystem>
#include <regex>
#include <vector>
#include <string>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-rectangle.h>
#include "bank_statement_converter/pdf_processor.h"
#include "rk_logger/logger.h"
#include "bank_statement_converter/exception_rk.h"
#include "bank_statement_converter/constants.h"
#include "bank_statement_converter/quick_sort.h"

std::string PdfProcessor::trim(const std::string str) const {
    RK_LOG("Trimming:", str, "\n");
    std::string result = str;
    size_t leading = result.find_first_not_of(" \t\n\r");
    if (leading != 0) {
        result = result.substr(leading);
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return (end == std::string::npos) ? "" : result.substr(0, end + 1);
}

/**
 * Uses std::filesystem to iterate through the files in the path provided. If it matches the regex pattern for
 * PDF files, it will save the file name for further processing. Otherwise, it won't add it, and instead will
 * add the file name to the file that holds the list of skipped files.
 */
void PdfProcessor::gatherPdfFiles(const std::string path) {
    RK_LOG("Gathering PDF files from directory: ", path, "\n");

    if (!std::filesystem::exists(path)) {
        RK_LOG(path, " doesnt exist\n");
        throw Exception(path + " doesn't exist");
    }

    const std::string SKIPPED_FILE_PATH = "./" + constants::OUTPUT_DIRECTORY + "/" + constants::SKIPPED_FILES_FILE_NAME;
    RK_LOG("Skipped files will be written to ", SKIPPED_FILE_PATH, ". Creating that file.\n");
    if (!skippedFiles) {
        RK_LOG("Could not open ", SKIPPED_FILE_PATH, " exiting\n");
        throw Exception("Could not open " + SKIPPED_FILE_PATH);
    }

    // Go through the files in the directory and add it to the list if it is a .pdf file.
    // Otherwise, add it to the skipped files.
    RK_LOG("Looking through files in ", path, "\n");
    skippedFiles << "-- SKIPPED FILES --\n";
    std::string fileName;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        fileName = entry.path().filename().string();
        RK_LOG("Processing file ", fileName, "\n");
        if (std::regex_match(fileName, constants::wells_fargo::regex::pdfFilePattern)) {
            RK_LOG("File ", fileName, " matched the pattern. Adding it to the list for further processing\n");
            pdfFiles.push_back(entry.path().string());
        }
        else {
            RK_LOG("File ", fileName, " didn't match the pattern. Not adding to to the list, instead adding it to skipped files\n");
            skippedFiles << fileName << "\n";
        }
    }

    skippedFiles << "\n";
    skippedFiles.close();

    RK_LOG("Finished gathering PDF files\n");
}


/**
 * Iterates through the files that were gathered in previous steps. It uses the Poppler library to parse through the PDF statements line-by-line.
 * It uses regex pattern matching to determine if a line is a transaction that needs to be saved. When it encounters a valid transaction, it'll
 * save it internally.
 */
void PdfProcessor::processPdfs(const std::string path) {
    RK_LOG("Processing PDFs in\"", path, "\"\n");

    const std::string skippedLinesPath = "./" + constants::OUTPUT_DIRECTORY + "/" + constants::SKIPPED_LINES_FILE_NAME;
    if (!skippedLines) {
        RK_LOG("Could not open ", skippedLinesPath, " exiting\n");
        throw Exception("Could not open " + skippedLinesPath);
    }
    skippedLines << "-- SKIPPED LINES --\n";

    // Parse the list of pdf files, extract the transaction data, and save it in a list
    for (const auto& file : pdfFiles) {
        RK_LOG("Processing file: ", file, "\n");

        // Get date from file name
        const size_t slashIndex = file.find("\\");
        const std::string month = file.substr(slashIndex + 1, 2);
        const std::string day = file.substr(slashIndex + 3, 2);
        const std::string year = "20" + file.substr(slashIndex + 5, 2);
        const bool isJanuaryStatement = month == "01";

        poppler::document* doc = poppler::document::load_from_file(file);
        if (!doc) {
            RK_LOG("Error: Could not open PDF file ", file, ". Exiting\n");
            throw Exception("Error: Could not open PDF file " + file);
        }
        else {
            RK_LOG("Opened pdf file ", file, " successfully\n");
        }

        // Iterate through the pages of the statement
        const int numPages = doc->pages();
        size_t transactionTitleCount = 0; /**< Count the number of times the transaction title is seen because we want to skip the title that's in the header of the statement*/
        bool lastFourFound = false;
        std::string lastFour;
        RK_LOG("Going through ", numPages, " pages\n");
        RK_LOG("Looking for \"", constants::wells_fargo::regex::TRANSACTION_SECTION_TITLE, "\" first\n");
        for (int i = 0; i < numPages; ++i) {
            RK_LOG("Processing page ", i, "\n");
            poppler::page* currentPage = doc->create_page(i);
            if (currentPage) {
                RK_LOG("Successfully opened page with poppler.\n");

                std::vector<char> byte_array = currentPage->text().to_utf8();
                std::stringstream currPageText;
                currPageText.write(byte_array.data(), byte_array.size());
                std::string line;

                // Go through line by line
                while (std::getline(currPageText, line)) {
                    RK_LOG("Processing line: ", line,  "\n");

                    // Extract last four
                    if (!lastFourFound) {
                        if (std::regex_search(line, constants::wells_fargo::regex::lastFourPattern)) {
                            RK_LOG("Line matched last four pattern. Extracting last four\n");
                            lastFour = line.substr(line.rfind(' ') + 1, 4);
                            RK_LOG("Extracted last four value: ", lastFour, "\n");
                            lastFourFound = true;
                            continue;
                        }
                    }

                    /* Before processing anything, find the second instance of the transaction title. This is because transactions come
                     after this title and we don't want to parse things that come before like credits.
                     Skip the 1st instance as that's in the document header/summary */
                    if (transactionTitleCount < 1) {
                        if (std::regex_search(line, constants::wells_fargo::regex::transactionTitlePattern)) {
                            RK_LOG("Found \"", constants::wells_fargo::regex::TRANSACTION_SECTION_TITLE, "\". Parsing transactions now\n");
                            transactionTitleCount++;
                        }

                        continue;
                    }

                    // Normal transactions
                    if (std::regex_match(line, constants::wells_fargo::regex::transactionPattern)) {
                        if (!std::regex_search(line, constants::wells_fargo::regex::transactionSkip)) {
                            RK_LOG("Line matched pattern. Saving\n");
                            Transaction* transaction = new Transaction();
                            generateTransaction(transaction, line, std::stoi(year), isJanuaryStatement, lastFour, false, false);
                            saveTransaction(transaction);
                        }
                        else {
                            RK_LOG("Line matched pattern, but is in the skip list. Skipping and adding to skipped file\n");
                            skippedLines << trim(line) << "\n";
                        }
                    }
                    // Interest charges
                    else if (std::regex_match(line, constants::wells_fargo::regex::transactionPatternInterest)) {
                        if (!std::regex_search(line, constants::wells_fargo::regex::transactionSkip)) {
                            RK_LOG("Line matched pattern. It is interest charge. Saving\n");
                            Transaction* transaction = new Transaction();
                            generateTransaction(transaction, line, std::stoi(year), isJanuaryStatement, lastFour, false, true);
                            saveTransaction(transaction);
                        }
                        else {
                            RK_LOG("Line matched pattern, but is in the skip list. Skipping and adding to skipped file\n");
                            skippedLines << trim(line) << "\n";
                        }
                    }
                    // Normal transactions that use the old format
                    else if (std::regex_match(line, constants::wells_fargo::regex::transactionPatternOld)) { 
                        if (!std::regex_search(line, constants::wells_fargo::regex::transactionSkip)) {
                            RK_LOG("Line matched old pattern. Saving\n");
                            Transaction* transaction = new Transaction();
                            generateTransaction(transaction, line, std::stoi(year), isJanuaryStatement, lastFour, true, false);
                            saveTransaction(transaction);
                        }
                        else {
                            RK_LOG("Line matched old pattern, but is in the skip list. Skipping and adding to skipped file\n");
                            skippedLines << trim(line) << "\n";
                        }
                    }
                    // Skipped, but possibly relevant lines
                    else if (std::regex_search(line, constants::wells_fargo::regex::transactionPatternSkippedRelevant)){
                        RK_LOG("Line didn't match, but is possibly relevant. Skipping and adding to skipped file\n");
                        skippedLines << trim(line) << "\n";
                    }
                }
            } else {
                RK_LOG("Error: Could not load page with poppler. Exiting.\n");
                throw Exception("Could not load page with poppler");
            }
        }
        delete doc;
    }
}

void PdfProcessor::saveTransaction(Transaction* transaction) {
    transactions.push_back(transaction);
}

void PdfProcessor::closeSkippedFilesFile() {
    skippedFiles.close();
}

void PdfProcessor::closeSkippedLinesFile() {
    skippedLines.close();
}

/**
 * For the values that it already knows/was passed into the function, it will simply populate the Transaction object with those values.
 * For the values that it doesn't know, it'll extract the values from the line that was passed in by searching the line for various characters
 * and using the indicies of those characters to extract substrings that have the desired value. There is special handling for January statements
 * with December transactions. In those cases, the year value is decreased by one, because even though the statement is from one year, the
 * transaction occured the year before.
 */
void PdfProcessor::generateTransaction(Transaction* transaction, std::string line, int year, const bool isJanuaryStatement, const std::string lastFour, const bool isOldFormat, const bool isInterestCharge) {
    RK_LOG("Generating transaction\n");

    if (!transaction) {
        throw Exception("Null transaction address passed to generateTransaction");
    }

    // Last four of account number
    RK_LOG("Setting Last Four to: ", lastFour, "\n");
    transaction->setLastFour(lastFour);
    if (!isOldFormat && !isInterestCharge) { // If new format, then remove last four from line. Old format doesn't have last four.
        const size_t lastFourIdx = line.find_first_not_of(" \t");
        line = line.substr(lastFourIdx + 4); 
    }

    // Date
    RK_LOG("Getting date\n");
    const size_t dateIdx = line.find("/");
    const int month = std::stoi(line.substr(dateIdx - 2, 2));
    const int day = std::stoi(line.substr(dateIdx + 1, 2));
    const bool isDecemberTransaction = month == 12;
    // Special handling if it's a January statement and a December transaction. Decrement year by 1, since the transaction occured the year before.
    if (isJanuaryStatement && isDecemberTransaction) {
        RK_LOG("It is a Jan statement and a Dec transaction. Decrementing year by 1\n");
        year--;
    }
    Date date(year, month, day);
    RK_LOG("Setting date to ", date.getDateString(), "\n");
    transaction->setDate(date);
    line = line.substr(line.find("/", dateIdx + 1) + 3); // Remove date from line

    // Reference number
    if (!isInterestCharge) { // Skip retrieving ref num for interest charge as they don't have it
        RK_LOG("Getting reference number\n");
        const size_t refNumIdx = line.find_first_not_of(" ");
        const std::string refNum = line.substr(refNumIdx, constants::wells_fargo::REF_NUM_SIZE); // The length of a reference number is known, so use that value here.
        RK_LOG("Setting reference number to ", refNum, "\n");
        transaction->setRefNum(refNum);
        line = line.substr(refNumIdx + constants::wells_fargo::REF_NUM_SIZE);
    }
    
    // Amount (currency)
    RK_LOG("Getting amount\n");
    line = trim(line);
    const size_t amountIdx = line.rfind(' ') + 1;
    std::string amountStr = line.substr(amountIdx);
    amountStr.erase(std::remove(amountStr.begin(), amountStr.end(), ','), amountStr.end()); // Remove comma
    const double amount = std::stod(amountStr);
    RK_LOG("Setting amount to ", amount, "\n");
    transaction->setCurrencyAmount(amount);
    line = line.substr(0, amountIdx - 1); // Remove amount from line

    // Name of transaction
    RK_LOG("Getting name\n");
    const size_t nameEndIdx = line.find_last_not_of(" \t\n\r");
    const std::string name = line.substr(0, nameEndIdx + 1);
    RK_LOG("Setting name to ", name, "\n");
    transaction->setName(name);

    RK_LOG("Created transaction: ", transaction->getInCsvFormat(), "\n");
}

void PdfProcessor::sortTransactions() {
    RK_LOG("Sorting transactions\n");
    QuickSort<Transaction>::quickSort(transactions, 0, transactions.size() - 1);
    RK_LOG("Finished sorting transactions\n");
}

/**
 * If there were no transactions, it'll just create a file with the contents "None".
 * Otherwise, it iterates through the internal transaction data and adds it to a file via std::ofstream.
 */
void PdfProcessor::generateCsvFile(const std::string fileName) {
    RK_LOG("Generating .csv file called ", fileName, "\n");

    std::ofstream csvFile("./" + constants::OUTPUT_DIRECTORY + "/" + fileName);
    if (!csvFile) {
        RK_LOG("Couldn't open ", fileName, "\n");
        throw Exception("Couldn't open " + fileName);
    }

    if (transactions.size() == 0) {
        RK_LOG("None\n");
        csvFile << "None";
        csvFile.close();
        return;
    }

    for (auto& transaction : transactions) {
        csvFile << transaction->getInCsvFormat() << "\n";
    }

    csvFile.close();
}

void PdfProcessor::printAllTransactions() const {
    RK_LOG("Printing all transactions\n");
    for (auto transaction : transactions) {
        RK_LOG(transaction->getInCsvFormat(), "\n");
    }
    RK_LOG("Finished printing all transactions\n");
}

size_t PdfProcessor::count() const {
    return transactions.size();
}