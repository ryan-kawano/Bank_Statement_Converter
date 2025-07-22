/**
 * @file transaction.h
 * @brief Header file for the Transaction class.
 */
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

#include <bank_statement_converter/date.h>
#include <bank_statement_converter/interfaces/i_transaction.h>

namespace bsc {

/**
 * @class Transaction
 * @brief Represents a transaction in a statement.
 */
class Transaction : public ITransaction {
public:
    /**
     * @brief Default constructor.
     */
    Transaction();

    /**
     * @brief Overloaded constructor.
     * 
     * @param id The unique identifier for the transaction (reference number, transaction id, etc).
     * @param accountNumber The account number associated with the transaction.
     * @param double The amount of the transaction in the specific currency.
     * @param std::string The currency.
     * @param Date The Date object representing the date of the transaction.
     * @param std::string The description of the transaction.
     */
    Transaction(const std::string& /* id */, const int /* accountNumber */, const double /* amount */, const std::string& currency, const Date& /* date */, const std::string& /* description */);

    std::string getId() const override;

    int getAccountNumber() const override;

    double getAmount() const override;

    std::string getCurrency() const override;
    
    /**
     * @brief Getter for Date.
     * 
     * @return Date object.
     */
    const Date& getDate() const override;

    std::string getDescription() const override;

    std::string asString() const override;

    void setId(const std::string&) override;
    void setAccountNumber(const int) override;

    void setAmount(const double) override;

    /**
     * @brief Setter for currency.
     * 
     * @param double The currency.
     */
    void setCurrency(const std::string&) override;

    /**
     * @brief Setter for name.
     * 
     * @param std::string The name.
     */
    void setDescription(const std::string&);

    /**
     * @brief Setter for date.
     * 
     * @param Date The Date object.
     */
    void setDate(const Date&);

    /**
     * @brief Overloaded <= operator.
     * 
     * @param Transaction The Transaction to compare to.
     * @return The result of the comparison.
     */
    bool operator<=(const ITransaction&) const override;

private:
    std::string id;
    int accountNumber;
    double amount;
    std::string currency;
    Date date;
    std::string description;
};

} // namespace bsc

#endif // #ifndef TRANSACTION_H
