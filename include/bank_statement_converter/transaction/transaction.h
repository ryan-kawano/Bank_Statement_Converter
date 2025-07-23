#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

#include <bank_statement_converter/date.h>
#include <bank_statement_converter/interfaces/i_transaction.h>

namespace bsc {

/**
 * @class Transaction
 * @brief Represents a purchase, withdrawal, credit, interest charge, etc in a bank statement.
 */
class Transaction : public ITransaction {
public:
    Transaction();

    /**
     * @brief Overloaded constructor.
     * 
     * @param id The unique identifier for the transaction (reference number, transaction id, etc).
     * @param accountNumber The account number associated with the transaction.
     * @param double The amount of the transaction.
     * @param currency The currency type, e.g., USD, EUR, JPY, etc.
     * @param date The Date object representing the date of the transaction.
     * @param description The description or name of the transaction.
     */
    Transaction(const std::string& id, const int accountNumber, const double amount, const std::string& currency, const Date& date, const std::string& description);

    std::string getId() const override;
    int getAccountNumber() const override;
    double getAmount() const override;
    std::string getCurrency() const override;
    const Date& getDate() const override;
    std::string getDescription() const override;

    /**
     * @brief Converts this transaction to a human-readable string representation.
     * 
     * @return The string representation.
     */
    std::string asString() const override;

    void setId(const std::string& id) override;
    void setAccountNumber(const int accountNumber) override;
    void setAmount(const double amount) override;
    void setCurrency(const std::string& currency) override;
    void setDescription(const std::string& description);
    void setDate(const Date& date);

    /**
     * @brief Overloaded <= operator.
     * 
     * Compares transactions based on their date. Earlier dates should come before later dates.
     */
    bool operator<=(const ITransaction& other) const override;

private:
    std::string id; /**< The unique identifier for the transaction (reference number, transaction id, etc) */
    int accountNumber; /**< The account number associated with the transaction */
    double amount;
    std::string currency; /**< The currency type, e.g., USD, EUR, JPY, etc */
    Date date; /**< The date of the transaction itself, not the statement it's a part of */
    std::string description; /**< The description or name of the transaction */
};

} // namespace bsc

#endif // #ifndef TRANSACTION_H
