/**
 * @file date.h
 * @brief Header file for the Date class.
 */
#ifndef DATE_H
#define DATE_H

#include <string>

/**
 * @class Date
 * @brief Simple class meant to represent a date in time.
 */
class Date {
public:
    /**
     * @brief Constructor.
     */
    Date();

    /**
     * @brief Overloaded constructor.
     * 
     * @param int year.
     * @param int month.
     * @param int day.
     */
    Date(const int, const int, const int);

    /**
     * @brief Copy constructor.
     * 
     * @param Date The Date object to copy from.
     */
    Date(const Date&);

    /**
     * @brief Formats the date in a user-friendly format and returns it. It will be in the format "[MM/DD/YYYY]".
     * 
     * @return The formatted date.
     */
    std::string getDateString() const;

    /**
     * @brief Overloaded assignment operator.
     * 
     * @param Date The Date whose data you want to copy.
     * 
     * @return The resulting Date object.
     */
    Date& operator=(const Date&);

    /**
     * @brief Overloaded "<=" operator meant for comparing dates to one another chronologically.
     * 
     * Ex. Date #1 is less than Date #2 if Date #1 happened earlier than Date #2.
     * 
     * @param Date The date to compare to.
     * 
     * @return The result of the comparison.
     */
    bool operator<=(const Date& other) const;

    /**
     * @brief Getter for year.
     * 
     * @return Year value.
     */
    int getYear() const;

    /**
     * @brief Getter for month.
     * 
     * @return Month value.
     */
    int getMonth() const;

    /**
     * @brief Getter for day.
     * 
     * @return Day value.
     */
    int getDay() const;
private:
    int year;
    int month;
    int day;
};

#endif
