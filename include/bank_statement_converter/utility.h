/**
 * @brief Various uility functions.
 */
#ifndef UTILITY_H
#define UTILITY_H

#include <string>

namespace bsc {
namespace utility {

    /**
     * @brief Trims leading and trailing whitespaces.
     * 
     * @param str The string to trim.
     * @return The trimmed string.
     */
    std::string trim(const std::string str);

}
}

#endif // #ifndef UTILITY_H
