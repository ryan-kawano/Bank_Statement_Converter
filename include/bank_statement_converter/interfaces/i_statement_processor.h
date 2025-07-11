#ifndef I_STATEMENT_PROCESSOR_H
#define I_STATEMENT_PROCESSOR_H

#include <filesystem>
#include <memory>

#include "bank_statement_converter/interfaces/i_statement.h"

class IStatementProcessor {
public:
    ~IStatementProcessor() = default;
    virtual std::shared_ptr<IStatement> processFile(const std::filesystem::path&) = 0;

private:
    virtual void openFile(const std::filesystem::path&) const = 0;
};

#endif // #ifndef I_STATEMENT_PROCESSOR_H
