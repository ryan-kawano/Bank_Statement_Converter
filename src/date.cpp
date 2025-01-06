/**
 * @file date.cpp
 * @brief Source file for the Date class.
 */
#include "wells_fargo_statement_converter/date.h"

Date::Date() {}

Date::Date(const int pYear, const int pMonth, const int pDay) : year(pYear), month(pMonth), day(pDay) {}

Date::Date(const Date& pDate) : year(pDate.year), month(pDate.month), day(pDate.day) {}

std::string Date::getDateString() {
    return "[" + std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year) + "]";
}

Date& Date::operator=(const Date& other) {
    if (this == &other) {
        return *this;
    }

    year = other.year;
    month = other.month;
    day = other.day;

    return *this;
}

/**
 * Checks if a date is less than or equal to another date. A date is "less than" 
 * another date if it is further in the past. Comparison starts broad, then gets
 * more narrow. For example, it starts with years, if they're the same it'll go to months and so on.
 */
bool Date::operator<=(const Date& other) const {
    if (year != other.year) {
        return year <= other.year;
    }
    if (month != other.month) {
        return month <= other.month;
    }
    return day <= other.day;
}

int const Date::getYear() {
    return year;
}

int const Date::getMonth() {
    return month;
}

int const Date::getDay() {
    return day;
}
