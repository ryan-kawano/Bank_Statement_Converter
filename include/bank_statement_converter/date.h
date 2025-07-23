#ifndef DATE_H
#define DATE_H

#include <string>

namespace bsc {

/**
 * @class Date
 * @brief Simple class meant to represent a date in time.
 */
class Date {
public:
    Date();
    Date(const int year, const int month, const int day);
    Date(const Date& date);

    /**
     * @brief Formats the date in a user-friendly format and returns it.
     * 
     * @return The formatted date.
     */
    std::string getDateString() const;

    Date& operator=(const Date&);

    /**
     * @brief Overloaded "<=" operator meant for comparing dates to one another chronologically.
     * 
     * Ex. Date #1 is less than Date #2 if Date #1 happened earlier than Date #2.
     */
    bool operator<=(const Date& other) const;

    int getYear() const;
    int getMonth() const;
    int getDay() const;

private:
    int year;
    int month;
    int day;
};

} // namespace bsc

#endif // #ifndef DATE_H
