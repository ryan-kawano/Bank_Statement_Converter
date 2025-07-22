#ifndef I_STATEMENT_H
#define I_STATEMENT_H

#include <filesystem>
#include <vector>
#include <string>
#include <memory>

#include <bank_statement_converter/interfaces/i_transaction.h>
#include <bank_statement_converter/date.h>

namespace bsc {

class IStatement {
public:
    using SkippedLines = std::vector<std::string>;

    virtual ~IStatement() = default;
    virtual std::filesystem::path getPath() const = 0;
    virtual const std::vector<std::shared_ptr<ITransaction>>& getTransactions() const = 0;
    virtual const Date& getDate() const = 0;
    virtual const SkippedLines& getSkippedLines() const = 0;
    virtual size_t getCount() const = 0;
    virtual void setPath(std::filesystem::path&) = 0;
    virtual void setDate(const Date&) = 0;
    virtual void addTransaction(std::shared_ptr<ITransaction>) = 0;
    virtual void addSkippedLine(const std::string&) = 0;
    virtual void sort() = 0;
    virtual bool operator<=(const IStatement&) const = 0;
};

} // namespace bsc

#endif // #ifndef I_STATEMENT_H
