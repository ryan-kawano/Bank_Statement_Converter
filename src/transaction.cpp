/**
 * @file transaction.cpp
 * @brief Source file for the Transaction class.
 */
#include <sstream>
#include <iomanip>
#include "wells_fargo_statement_converter/transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(const double pCurrencyAmount, const std::string pName, const Date& pDate, const std::string pReferenceNum, const std::string pLastFour)
    : currencyAmount(pCurrencyAmount), name(pName), date(pDate), referenceNum(pReferenceNum), lastFour(pLastFour) {}

std::string Transaction::getInCsvFormat() const {
    std::ostringstream oss;
    // Last four
    oss << "\"" << lastFour << "\",";

    // Transaction date
    oss << "\"";
    oss << std::setw(2) << std::setfill('0') << date.getMonth();
    oss << "/";
    oss << std::setw(2) << std::setfill('0') << date.getDay();
    oss << "/";
    oss << std::setw(4) << date.getYear();
    oss << "\",";

    // Reference number
    oss << "\"" << referenceNum << "\",";

    // Name
    oss << "\"" << name << "\",";

    // Amount
    oss << "\"";
    oss << std::fixed << std::setprecision(2) << -currencyAmount;
    oss << "\"";

    return oss.str();
}

const Date& Transaction::getDate() const {
    return date;
}

void Transaction::setCurrencyAmount(const double pCurrencyAmount) {
    currencyAmount = pCurrencyAmount;
}

void Transaction::setName(const std::string pName) {
    name = pName;
}

void Transaction::setDate(const Date& pDate) {
    date = pDate;
}

void Transaction::setRefNum(const std::string pRefNum) {
    referenceNum = pRefNum;
}

void Transaction::setLastFour(const std::string pLastFour) {
    lastFour = pLastFour;
}
