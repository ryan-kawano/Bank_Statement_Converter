#ifndef I_TRANSACTION_H
#define I_TRANSACTION_H

#include <string>

#include <bank_statement_converter/date.h>

namespace bsc {

class ITransaction {
public:
    virtual ~ITransaction() = default;

    virtual std::string getId() const = 0;
    virtual int getAccountNumber() const = 0;
    virtual double getAmount() const = 0;
    virtual std::string getCurrency() const = 0;
    virtual const Date& getDate() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string asString() const = 0;

    virtual void setId(const std::string& id) = 0;
    virtual void setAccountNumber(const int accountNumber) = 0;
    virtual void setAmount(const double amount) = 0;
    virtual void setCurrency(const std::string& currency) = 0;
    virtual void setDate(const Date& date) = 0;
    virtual void setDescription(const std::string& description) = 0;

    /**
     * @brief Overloaded <= operator to compare Transactions.
     * 
     * Transactions shall be compared by their dates in chronological order, i.e., earlier transactions come before
     * later transactions.
     */
    virtual bool operator<=(const ITransaction& other) const = 0;
};

} // namespace bsc

#endif // #ifndef I_TRANSACTION_H
