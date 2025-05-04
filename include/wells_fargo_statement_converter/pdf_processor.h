/**
 * @file pdf_processor.h
 * @brief Header file for the PdfProcessor class.
 */
#ifndef PDF_PROCESSOR_H
#define PDF_PROCESSOR_H

#include <string>
#include <fstream>
#include "constants.h"
#include "transaction.h"

/**
 * @class PdfProcessor
 * @brief This class is responsible for processing PDF bank statements and converting them to a CSV file.
 */
class PdfProcessor  {
public:
    /**
     * @brief Default constructor.
     */
    PdfProcessor() : skippedFiles("./" + constants::OUTPUT_DIRECTORY + "/" + constants::SKIPPED_FILES_FILE_NAME), skippedLines("./" + constants::OUTPUT_DIRECTORY + "/" + constants::SKIPPED_LINES_FILE_NAME) {};

    /**
     * @brief Helper function to remove leading and trailing whitespace (including newlines).
     * 
     * @param std::string The string to trim.
     * 
     * @return The trimmed string.
     */
    std::string trim(const std::string) const;

    /**
     * @brief Goes through the directory that holds the PDF statements and adds them to a list. It only adds files that match a certain pattern.
     * 
     * @param std::string The path to the directory that contains the PDF statements.
     */
    void gatherPdfFiles(const std::string);

    /**
     * @brief Goes through the gathered PDF statements, extracts the transaction data, and saves it internally.
     * 
     * @param std::string The path to the directory that contains the PDF statements.
     */
    void processPdfs(const std::string);

    /**
     * @brief Utility function that closes the "Skipped Files" file.
     */
    void closeSkippedFilesFile();

    /**
     * @brief Utility function that closes the "Skipped Lines" file.
     */    
    void closeSkippedLinesFile();

    /**
     * @brief Populates a Transaction object with the provided arguments.
     * 
     * @param Transaction The Transaction object to be populated.
     * @param std::string The line from the statement that has the transaction information.
     * @param int The year of the statement. NOT the year of the transaction.
     * @param bool Whether or not the transaction was part of a January statement.
     * @param std::string The last four digits of the account.
     * @param bool Whether or not the transaction is part of a statement that uses the old format.
     * @param bool Whether or not the transaction is an interest charge.
     */
    void generateTransaction(Transaction*, std::string, const int, const bool, const std::string, const bool, const bool);

    /**
     * @brief Sorts the internally stored transactions.
     */
    void sortTransactions();

    /**
     * @brief Generates the final CSV file from the processed data.
     */
    void generateCsvFile(const std::string);

    /**
     * @brief Utility function to print all of the transaction to the console.
     */
    void printAllTransactions() const;
private:
    std::vector<std::string> pdfFiles;
    std::ofstream skippedFiles; /**< Any files that were skipped during the file gathering process */
    std::ofstream skippedLines; /**< Any lines in the PDF statements that were skipped during processing */
    std::vector<Transaction*> transactions; /**< Container to hold all of the transaction data */
};

#endif