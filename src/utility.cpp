#include <bank_statement_converter/utility.h>

namespace bsc {
namespace utility {

    std::string trim(std::string str) {
        size_t leading = str.find_first_not_of(" \t\n\r");
        if (leading != std::string::npos) {
            str = str.substr(leading);
        } else {
            return "";
        }
        size_t trailing = str.find_last_not_of(" \t\n\r");
        return (trailing == std::string::npos) ? "" : str.substr(0, trailing + 1);
    }

}
}
