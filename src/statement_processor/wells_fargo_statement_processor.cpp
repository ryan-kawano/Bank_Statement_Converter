#include <rk_logger/logger.h>
#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/utility.h>
#include <bank_statement_converter/statement_processor/wells_fargo_statement_processor.h>
#include <bank_statement_converter/transaction/transaction.h>
#include <bank_statement_converter/transaction/transaction_builder.h>

namespace bsc {

static constexpr int MAX_LINE_LENGTH = 30;

void WellsFargoStatementProcessor::processLines(std::shared_ptr<IStatement> statement, IStatementFileProcessor::StatementLines lines) const {
    bool isDateFound = false;
    bool isJanuaryStatement = false;
    std::string month = "00";
    std::string day = "00";
    std::string year = "0000";
    int transactionTitleCount = 0;
    std::string currency = "USD"; // Hardcoded for now, fix later

    for (const auto& [page_num, page_lines] : lines) {
        RK_LOG("Processing lines from page ", page_num, "\n");

        for (const auto& line : page_lines) {
            RK_LOG("Processing line: ", line.substr(0, MAX_LINE_LENGTH), (line.size() > MAX_LINE_LENGTH ? "..." : ""), "\n");

            // Extract Date
            if (!isDateFound) {
                std::smatch matchResults;
                /**
                 * The regex below would match strings like:
                 * Statement Period 01/15/2025 to 02/15/2025
                 * 01/15/2025 to 02/15/2025
                 */
                if (std::regex_search(line, matchResults, std::regex("Statement Period (\\d{2}/\\d{2}/\\d{4}) to (\\d{2}/\\d{2}/\\d{4})")) || std::regex_search(line, matchResults, std::regex("(\\d{2}/\\d{2}/\\d{4}) to (\\d{2}/\\d{2}/\\d{4})"))) {
                    RK_LOG("Line matched statement period pattern. Extracting date\n");
                    const std::string date = matchResults[2];
                    month = date.substr(0, 2);
                    day = date.substr(3, 2);
                    year = date.substr(6, 4);
                    isJanuaryStatement = month == "01";
                    statement->setDate(Date(std::stoi(year), std::stoi(month), std::stoi(day)));
                    RK_LOG("Set date to ", month, "/", day, "/", year, "\n");
                    isDateFound = true;
                    continue;
                }
            }

            /**
             * Before processing anything, find the second instance of the transaction title. This is because transactions come
             * after this title and we don't want to parse things that come before like credits.
             * Skip the 1st instance as that's in the document header/summary
             */
            if (transactionTitleCount < 1) {
                if (std::regex_search(line, bsc::constants::wells_fargo::regex::transactionTitlePattern)) {
                    RK_LOG("Found \"", bsc::constants::wells_fargo::regex::TRANSACTION_SECTION_TITLE, "\". Parsing transactions now\n");
                    transactionTitleCount++;
                }

                continue;
            }

            // Process transactions based on their type
            // Normal transactions
            if (std::regex_match(line, bsc::constants::wells_fargo::regex::transactionPattern)) {
                if (!std::regex_search(line, bsc::constants::wells_fargo::regex::transactionSkip)) {
                    RK_LOG("Line matched pattern. Saving\n");
                    std::shared_ptr<ITransaction> transaction = TransactionBuilder::buildTransaction(line, std::stoi(year), currency, isJanuaryStatement, false, false);
                    statement->addTransaction(transaction);
                }
                else {
                    RK_LOG("Line matched pattern, but is in the skip list. Skipping and adding to skipped file\n");
                    statement->addSkippedLine(bsc::utility::trim(line) + "\n");
                }
            }
            // Interest charges
            else if (std::regex_match(line, bsc::constants::wells_fargo::regex::transactionPatternInterest)) {
                if (!std::regex_search(line, bsc::constants::wells_fargo::regex::transactionSkip)) {
                    RK_LOG("Line matched pattern. It is interest charge. Saving\n");
                    std::shared_ptr<ITransaction> transaction = TransactionBuilder::buildTransaction(line, std::stoi(year), currency, isJanuaryStatement, false, true);
                    statement->addTransaction(transaction);
                }
                else {
                    RK_LOG("Line matched pattern, but is in the skip list. Skipping and adding to skipped file\n");
                    statement->addSkippedLine(bsc::utility::trim(line) + "\n");
                }
            }
            // Normal transactions that use the old format
            else if (std::regex_match(line, bsc::constants::wells_fargo::regex::transactionPatternOld)) {
                if (!std::regex_search(line, bsc::constants::wells_fargo::regex::transactionSkip)) {
                    RK_LOG("Line matched old pattern. Saving\n");
                    std::shared_ptr<ITransaction> transaction = TransactionBuilder::buildTransaction(line, std::stoi(year), currency, isJanuaryStatement, true, false);
                    statement->addTransaction(transaction);
                }
                else {
                    RK_LOG("Line matched old pattern, but is in the skip list. Skipping and adding to skipped file\n");
                    statement->addSkippedLine(bsc::utility::trim(line) + "\n");
                }
            }
            else /*if (std::regex_search(line, bsc::constants::wells_fargo::regex::transactionPatternSkippedRelevant)) */ {
                // Skipped, but possibly relevant lines
                /*RK_LOG("Line didn't match, but is possibly relevant. Skipping and adding to skipped file\n");*/
                statement->addSkippedLine(bsc::utility::trim(line) + "\n");
            }
        }
    }
}

} // namespace bsc
