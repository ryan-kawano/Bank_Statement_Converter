#ifndef EXCEPTION_RK_H
#define EXCEPTION_RK_H

#include <exception>
#include <string>

namespace bsc {

class Exception : public std::exception {
private:
    std::string message;
public:
    explicit Exception(const std::string&);
    const char* what() const noexcept override;
};

} // namespace bsc

#endif
