/**
 * @file constants.h
 * @brief Contains global constants used throughout the program.
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <regex>

namespace constants {

// Known values
constexpr size_t REF_NUM_SIZE = 17; /**< The amount of characters in a reference number */

// File and directory names
inline const std::string OUTPUT_DIRECTORY = "output";
inline const std::string PDF_DIRECTORY = "statements_pdf";
inline const std::string CSV_FILE_NAME = "combined_statements.csv";
inline const std::string SKIPPED_LINES_FILE_NAME = "skipped_lines.txt";
inline const std::string SKIPPED_FILES_FILE_NAME = "skipped_files.txt";

namespace regex {

    // Patterns
    inline const std::string PDF_FILE_NAME = "[0-9]{6} WellsFargo\\.pdf"; /**< ie. "102324 WellsFargo.pdf". Represents the standard file name pattern used by Wells Fargo when downloading statements from them */
    inline const std::string TRANSACTION = "^\\s*(\\d+)\\s+(\\d{2}/\\d{2})\\s+(\\d{2}/\\d{2})\\s+(\\S+)\\s+(.+?)\\s+((\\d|,)+\\.\\d{2})\\s*$";
    inline const std::string TRANSACTION_OLD = "^\\s*(\\d{2}/\\d{2})\\s+(\\d{2}/\\d{2})\\s+(\\S+)\\s+(.+?)\\s+((\\d|,)+\\.\\d{2})\\s*$"; /**< wells Fargo switched their format around August 2023. Old format didn't have last 4 of card for each transaction */
    inline const std::string TRANSACTION_INTEREST = "^\\s*(\\d{2}/\\d{2})\\s+(\\d{2}/\\d{2})\\s+INTEREST CHARGE ON PURCHASES\\s+((\\d|,)+\\.\\d{2})\\s*$"; // Interest charges don't have "card ending in" or "reference num"
    inline const std::string TRANSACTION_SECTION_TITLE = "Purchases, Balance Transfers & Other Charges"; /**< This text comes before transactions are listed */
    inline const std::string ONLINE_PAYMENT = "ONLINE PAYMENT";
    inline const std::string LAST_STATEMENT_BALANCE = "LAST STATEMENT BAL FROM ACCT ENDING";
    inline const std::string SKIP_LIST = "(" + ONLINE_PAYMENT + "|" + LAST_STATEMENT_BALANCE + ")"; /**< These are patterns that will match the transaction pattern, but are not needed, so they are added to this pattern to skip them explicitly */
    inline const std::string SKIPPED_RELEVANT = "((\\d|,)+\\.\\d{2})|(\\$+)"; /**< For capturing lines that were possibly skipped on accident */
    inline const std::string LAST_FOUR = "(Ending in|Account ending in)";

    // Regex objects
    const std::regex pdfFilePattern(PDF_FILE_NAME);
    const std::regex transactionPattern(TRANSACTION);
    const std::regex transactionPatternOld(TRANSACTION_OLD);
    const std::regex transactionPatternInterest(TRANSACTION_INTEREST);
    const std::regex transactionTitlePattern(TRANSACTION_SECTION_TITLE);
    const std::regex transactionSkip(SKIP_LIST);
    const std::regex transactionPatternSkippedRelevant(SKIPPED_RELEVANT);
    const std::regex lastFourPattern(LAST_FOUR);

} // namespace regex

} // namespace constants

#endif
