#ifndef TRANSACTION_BUILDER_H
#define TRANSACTION_BUILDER_H

#include <memory>

#include <rk_logger/logger.h>
#include <bank_statement_converter/utility.h>
#include <bank_statement_converter/transaction/transaction.h>

namespace bsc {

/**
 * @class TransactionBuilder
 * @brief Responsible for building transactions given certain transaction data.
 */
class TransactionBuilder {
public:
    /**
     * @brief Builds a transaction with the provided data.
     * 
     * @param line Line from a bank statement that contains information about the transaction.
     * @param year Year of the statement that the transaction is from.
     * @param currency Currency type of the transaction, e.g., USD, EUR, JPY, etc
     * @param isJanuaryStatement Whether the statement is from January.
     * @param isOldFormat Whether the statement is in the old format.
     * @param isInterestCharge Whether the transaction is an interest charge.
     * @return A transaction populated with the given data.
     */
    static std::shared_ptr<ITransaction> buildTransaction(std::string line, int year, const std::string currency, const bool isJanuaryStatement, const bool isOldFormat = false, const bool isInterestCharge = false) {
        RK_LOG("Generating transaction\n");
        std::shared_ptr<ITransaction> transaction = std::make_shared<Transaction>();

        // Account Number
        RK_LOG("Extracing account number from line\n");
        std::smatch matches;
        if (std::regex_search(line, matches, std::regex("\\d{4}"))) {
            RK_LOG("Setting account number to ", matches[0], "\n");
            transaction->setAccountNumber(std::stoi(matches[0]));
        }
        else {
            RK_LOG("Could not extract account number. Setting as 0000\n");
            transaction->setAccountNumber(0000);
        }
        if (!isOldFormat && !isInterestCharge && matches.size() > 0) { // If new format, then remove last four from line. Old format doesn't have last four.
            line = line.substr(matches.position(0) + 4);
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

        // Reference Number
        if (!isInterestCharge) {
            // Skip retrieving ref num for interest charge as they don't have it
            RK_LOG("Getting reference number\n");
            const size_t refNumIdx = line.find_first_not_of(" ");
            const std::string refNum = line.substr(refNumIdx, bsc::constants::wells_fargo::REF_NUM_SIZE); // The length of a reference number is known, so use that value here.
            RK_LOG("Setting reference number to ", refNum, "\n");
            transaction->setId(refNum);
            line = line.substr(refNumIdx + bsc::constants::wells_fargo::REF_NUM_SIZE);
        }
        else {
            transaction->setId("N/A");
        }
        
        // Amount
        RK_LOG("Getting amount\n");
        line = bsc::utility::trim(line);
        const size_t amountIdx = line.rfind(' ') + 1;
        std::string amountStr = line.substr(amountIdx);
        amountStr.erase(std::remove(amountStr.begin(), amountStr.end(), ','), amountStr.end()); // Remove comma
        const double amount = std::stod(amountStr);
        RK_LOG("Setting amount to ", amount, "\n");
        transaction->setAmount(amount);
        line = line.substr(0, amountIdx - 1); // Remove amount from line

        // Description
        RK_LOG("Getting description\n");
        const size_t nameEndIdx = line.find_last_not_of(" \t\n\r");
        const std::string name = line.substr(0, nameEndIdx + 1);
        RK_LOG("Setting description to ", name, "\n");
        transaction->setDescription(name);

        // Currency
        transaction->setCurrency(currency);

        RK_LOG("Created transaction: ", transaction->asString(), "\n");

        return transaction;
    }
};

} // namespace bsc

#endif // #ifndef TRANSACTION_BUILDER_H
