#include <rk_logger/logger.h>
#include <bank_statement_converter/statement/statement_manager.h>
#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/statement_processor/pdf_statement_processor.h>
#include <bank_statement_converter/statement_processor/statement_file_processor_factory.h>
#include <bank_statement_converter/quick_sort.h>

namespace bsc {

void StatementManager::parseStatements(const std::vector<StatementFileManager::File>& files) {
    RK_LOG("Processing ", files.size(), " statements\n");

    StatementFileProcessorFactory factory;

    // Parse the list of pdf files, extract the transaction data, and save it in a list
    for (const auto& file : files) {
        RK_LOG("Processing file: ", file.first, "\n");

        std::shared_ptr<IStatement> statement = StatementFileProcessorFactory::createProcessor(file.second)->processFile(file.first);
        if (statement) {
            statements.push_back(statement);
        }
        else {
            skippedFiles.push_back(file.first);
        }
    }
}

void StatementManager::sort() {
    RK_LOG("Sorting ", statements.size(), " statements\n");

    // Sort the transactions within the statements first
    for (const auto& statement : statements) {
        statement->sort();
    }

    // Then, sort the statements themselves
    QuickSort<IStatement>::quickSort(statements, 0, statements.size() - 1);
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

size_t StatementManager::getCount() const {
    return statements.size();
}

} // namespace bsc
