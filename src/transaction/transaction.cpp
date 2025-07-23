/**
 * @file transaction.cpp
 * @brief Source file for the Transaction class.
 */
#include <rk_logger/logger.h>
#include <bank_statement_converter/transaction/transaction.h>

namespace bsc {

Transaction::Transaction() {}

Transaction::Transaction(const std::string& id, const int accountNumber, const double amount, const std::string& currency, const Date& date, const std::string& description)
    : id(id), accountNumber(accountNumber), amount(amount), currency(currency), date(date), description(description) {}

std::string Transaction::getId() const {
    return id;
}

int Transaction::getAccountNumber() const {
    return accountNumber;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getCurrency() const {
    return currency;
}

const Date& Transaction::getDate() const {
    return date;
}

std::string Transaction::getDescription() const {
    return description;
}

std::string Transaction::asString() const {
    return std::string("Acc Num: ") + std::to_string(accountNumber) + ", id: " + id + ", date: " + date.getDateString() + ", description: " + description + ", amount: " + std::to_string(amount);
}

void Transaction::setId(const std::string& id) {
    this->id = id;
}

void Transaction::setAccountNumber(const int accountNumber) {
    this->accountNumber = accountNumber;
}

void Transaction::setAmount(const double amount) {
    this->amount = amount;
}

void Transaction::setCurrency(const std::string& currency) {
    this->currency = currency;
}

void Transaction::setDescription(const std::string& description) {
    this->description = description;
}

void Transaction::setDate(const Date& date) {
    this->date = date;
}

bool Transaction::operator<=(const ITransaction& other) const {
    return this->getDate() <= other.getDate();
}

} // namespace bsc
