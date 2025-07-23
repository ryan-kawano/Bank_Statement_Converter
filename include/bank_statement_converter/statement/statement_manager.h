#ifndef STATEMENT_MANAGER_H
#define STATEMENT_MANAGER_H

#include <bank_statement_converter/interfaces/i_statement.h>
#include <bank_statement_converter/statement/statement_file_manager.h>

namespace bsc {

/**
 * @class StatementManager
 * @brief Responsible for handling statement data.
 * 
 * Handles converting statement files to class representations, e.g., IStatement.
 * Saves statements in this form and processes them.
 */
class StatementManager {
public:
    using Statements = std::vector<std::shared_ptr<IStatement>>;

    /**
     * @brief Parses statement files and saves them as statement objects.
     * 
     * @param files Statement files to parse.
     */
    void parseStatements(const std::vector<StatementFileManager::File>& files);

    void sort();
    const Statements& getStatements() const;
    const IStatement::SkippedLines getSkippedLines() const;
    size_t getStatementCount() const;
    
private:
    Statements statements;
    std::vector<std::filesystem::path> skippedFiles;
};

} // namespace bsc

#endif // #ifndef STATEMENT_MANAGER_H
