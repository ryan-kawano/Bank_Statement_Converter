#include <bank_statement_converter/date.h>

namespace bsc {

Date::Date() {}

Date::Date(const int year, const int month, const int day) : year(year), month(month), day(day) {}

Date::Date(const Date& date) : year(date.year), month(date.month), day(date.day) {}

std::string Date::getDateString() const {
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

int Date::getYear() const{
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

} // namespace bsc
