#ifndef I_STATEMENT_FILE_PROCESSOR_H
#define I_STATEMENT_FILE_PROCESSOR_H

#include <filesystem>
#include <memory>
#include <unordered_map>

#include <bank_statement_converter/interfaces/i_statement.h>

namespace bsc {

class IStatementFileProcessor {
public:
    using StatementLines = std::unordered_map<int, std::vector<std::string>>;
    virtual ~IStatementFileProcessor() = default;
    virtual std::shared_ptr<IStatement> processFile(const std::filesystem::path&) = 0;
};

} // namespace bsc

#endif // #ifndef I_STATEMENT_FILE_PROCESSOR_H
