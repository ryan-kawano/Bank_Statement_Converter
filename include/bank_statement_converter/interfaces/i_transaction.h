#ifndef I_TRANSACTION_H
#define I_TRANSACTION_H

#include <string>

#include "bank_statement_converter/date.h"

class ITransaction {
public:
    virtual ~ITransaction() = default;
    virtual std::string getId() const = 0;
    virtual int getAccountNumber() const = 0;
    virtual double getAmount() const = 0;
    virtual std::string getCurrency() const = 0;
    virtual const Date& getDate() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void setAmount(const double) = 0;
    virtual void setCurrency(const std::string&) = 0;
    virtual void setDate(const Date&) = 0;
    virtual void setDescription(const std::string&) = 0;
    virtual bool operator<=(const ITransaction&) = 0;
};

#endif // #ifndef I_TRANSACTION_H
