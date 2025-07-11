#include <rk_logger/logger.h>
#include <bank_statement_converter/statement/statement_manager.h>
#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/statement_processor/pdf_statement_processor.h>
#include <bank_statement_converter/statement_processor/statement_processor_factory.h>

void StatementManager::parseStatements(const std::vector<StatementFileManager::File>& files) {
    RK_LOG("Processing ", files.size(), " statements\n");

    StatementProcessorFactory factory;

    // Parse the list of pdf files, extract the transaction data, and save it in a list
    for (const auto& file : files) {
        RK_LOG("Processing file: ", file.first, "\n");

        std::unique_ptr<IStatementProcessor> statementProcessor = factory.createProcessor(file.second);
        std::shared_ptr<IStatement> statement = statementProcessor->processFile(file.first);
        statements.push_back(statement);
    }
}

void StatementManager::sort() {
    for (const auto& statement : statements) {
        statement->sort();
    }
}

const StatementManager::Statements& StatementManager::getStatements() const {
    return statements;
}

const IStatement::SkippedLines StatementManager::getSkippedLines() const {
    IStatement::SkippedLines result;
    for (const auto& statement : statements) {
        for (const auto& line : statement->getSkippedLines()) {
            result.push_back(line);
        }
    }
    return result;
}

const int StatementManager::getCount() const {
    return statements.size();
}
