#ifndef I_STATEMENT_FILE_PROCESSOR_H
#define I_STATEMENT_FILE_PROCESSOR_H

#include <filesystem>
#include <memory>
#include <unordered_map>

#include <bank_statement_converter/interfaces/i_statement.h>

namespace bsc {

/**
 * @class IStatementFileProcessor
 * @brief This interface defines the contract for classes that are responsible for parsing statement files
 * and extracting the data. Once it has extracted the data, it shall delegate the actual processing
 * of that data to other classes.
 */
class IStatementFileProcessor {
public:
    using StatementLines = std::unordered_map<int, std::vector<std::string>>;
    virtual ~IStatementFileProcessor() = default;

    /**
     * @brief Processes a statement file at a given path and returns the created Statement.
     * 
     * Once it has extracted the data, it shall delegate the actual processing of the data to
     * other classes.
     * 
     * @param path The path to the statement file.
     * @return The created statement.
     */
    virtual std::shared_ptr<IStatement> processFile(const std::filesystem::path& path) = 0;
};

} // namespace bsc

#endif // #ifndef I_STATEMENT_FILE_PROCESSOR_H
