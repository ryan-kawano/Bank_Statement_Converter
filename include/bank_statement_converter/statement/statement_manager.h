#ifndef STATEMENT_MANAGER_H
#define STATEMENT_MANAGER_H

#include <bank_statement_converter/interfaces/i_statement.h>
#include <bank_statement_converter/statement/statement_file_manager.h>

class StatementManager {
public:
    using Statements = std::vector<std::shared_ptr<IStatement>>;

    void parseStatements(const std::vector<StatementFileManager::File>& files);
    void sort();
    const Statements& getStatements() const;
    const IStatement::SkippedLines getSkippedLines() const;
    const int getCount() const;
    
private:
    Statements statements;
};

#endif // #ifndef STATEMENT_MANAGER_H
