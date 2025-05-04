/**
 * @file transaction.h
 * @brief Header file for the Transaction class.
 */
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "date.h"

/**
 * @class Transaction
 * @brief Represents a transaction in a statement.
 */
class Transaction {
public:
    /**
     * @brief Default constructor.
     */
    Transaction();

    /**
     * @brief Overloaded constructor.
     * 
     * @param double The currency amount of the transaction.
     * @param std::string The name of the transaction.
     * @param Date The Date object representing the date of the transaction.
     * @param std::string The reference number of the transaction.
     * @param std::string The last four digits of the account number of the transaction.
     */
    Transaction(const double /* currencyAmount */, const std::string /* name */, const Date& /* date */, const std::string /* reference num */, const std::string /* last four */);

    /**
     * @brief Accesses the member values that hold the transaction data and combines them all together, separated by commas.
     * 
     * Example output:
     * "1234","04/18/2023","78G41DS8VD89SF891","MCDONALDS RESTAURANT","-15.34"
     * 
     * @return The formatted csv string.
     */
    std::string getInCsvFormat() const;

    /**
     * @brief Getter for Date.
     * 
     * @return Date object.
     */
    const Date& getDate() const;

    /**
     * @brief Setter for currencyAmount.
     * 
     * @param double The currency amount.
     */
    void setCurrencyAmount(const double);

    /**
     * @brief Setter for name.
     * 
     * @param std::string The name.
     */
    void setName(const std::string);

    /**
     * @brief Setter for date.
     * 
     * @param Date The Date object.
     */
    void setDate(const Date&);

    /**
     * @brief Setter for reference number.
     * 
     * @param std::string The reference number.
     */
    void setRefNum(const std::string);

    /**
     * @brief Setter for last four.
     * 
     * @param The last four.
     */
    void setLastFour(const std::string);
private:
    double currencyAmount;
    std::string name;
    Date date;
    std::string referenceNum;
    std::string lastFour;
};

#endif