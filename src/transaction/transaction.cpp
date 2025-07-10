/**
 * @file transaction.cpp
 * @brief Source file for the Transaction class.
 */
#include "bank_statement_converter/transaction/transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(const std::string& id, const int accountNumber, const double amount, const std::string currency, const Date& date, const std::string description)
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

bool Transaction::operator<=(const ITransaction& other) {
    return this->getDate() <= other.getDate();
}
