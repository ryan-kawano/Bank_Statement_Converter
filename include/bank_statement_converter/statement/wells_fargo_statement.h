#ifndef WELLS_FARGO_STATEMENT_H
#define WELLS_FARGO_STATEMENT_H

#include <bank_statement_converter/interfaces/i_statement.h>

namespace bsc {

class WellsFargoStatement : public IStatement {
public:
    WellsFargoStatement() = default;

    std::filesystem::path getPath() const override;
    const std::vector<std::shared_ptr<ITransaction>>& getTransactions() const override;
    const Date& getDate() const override;
    const SkippedLines& getSkippedLines() const override;
    size_t getCount() const override;

    void setPath(std::filesystem::path&) override;
    void setDate(const Date&) override;
    void addTransaction(std::shared_ptr<ITransaction>) override;
    void addSkippedLine(const std::string&) override;
    
    void sort() override;
    bool operator<=(const IStatement&) const override;

private:
    std::filesystem::path path;
    std::vector<std::shared_ptr<ITransaction>> transactions;
    Date date;
    SkippedLines skippedLines;
};

} // namespace bsc

#endif // #ifndef WELLS_FARGO_STATEMENT_H
