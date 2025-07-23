#ifndef I_STATEMENT_PROCESSOR_H
#define I_STATEMENT_PROCESSOR_H

#include <bank_statement_converter/interfaces/i_statement_file_processor.h>

namespace bsc {

/**
 * @class IStatementProcessor
 * @brief This interface defines the contract for classes that are responsible for processing data extracted
 * from statements and saving the data as an internal representation of a statement.
 */
class IStatementProcessor {
public:
    virtual ~IStatementProcessor() = default;
    virtual void processLines(std::shared_ptr<IStatement> statement, bsc::IStatementFileProcessor::StatementLines lines) const = 0;
};

} // namespace bsc

#endif // #ifndef I_STATEMENT_PROCESSOR_H
