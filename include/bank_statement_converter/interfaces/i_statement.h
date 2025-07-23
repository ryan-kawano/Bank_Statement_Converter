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
    virtual size_t getTransactionCount() const = 0;

    virtual void setPath(std::filesystem::path& path) = 0;
    virtual void setDate(const Date& date) = 0;
    virtual void addTransaction(std::shared_ptr<ITransaction> transaction) = 0;

    /**
     * @brief Adds a line from a statement that was skipped to a container of skipped lines.
     * 
     * @param line The skipped line.
     */
    virtual void addSkippedLine(const std::string& line) = 0;

    virtual void sort() = 0;

    /**
     * @brief Overloaded <= operator to compare statements.
     * 
     * Statement should be compared by their dates
     * in chronological order, i.e., earlier statements come before later statements.
     */
    virtual bool operator<=(const IStatement& other) const = 0;
};

} // namespace bsc

#endif // #ifndef I_STATEMENT_H
