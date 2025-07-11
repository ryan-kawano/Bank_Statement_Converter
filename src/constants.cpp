#include "bank_statement_converter/constants.h"

namespace constants {
    const std::unordered_map<std::string, constants::Bank> BANKS = {
        { "Wells Fargo", constants::Bank::WELLS_FARGO }
    };
} // namespace constants