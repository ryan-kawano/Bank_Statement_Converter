#include <bank_statement_converter/exception_rk.h>

namespace bsc {

Exception::Exception(const std::string& msg) : message(msg) {}

const char* Exception::what() const noexcept {
    return message.c_str();
}

} // namespace bsc
