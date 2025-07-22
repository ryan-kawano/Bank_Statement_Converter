#include <bank_statement_converter/constants.h>

namespace bsc {
namespace constants {

    const std::unordered_map<std::string, bsc::constants::Bank> BANKS = {
        { "Wells Fargo", bsc::constants::Bank::WELLS_FARGO }
    };

} // namespace constants
} // namespace bsc
