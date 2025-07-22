#ifndef I_STATEMENT_PROCESSOR_H
#define I_STATEMENT_PROCESSOR_H

#include <bank_statement_converter/interfaces/i_statement_file_processor.h>

namespace bsc {

class IStatementProcessor {
public:
    virtual ~IStatementProcessor() = default;
    virtual void processLines(std::shared_ptr<IStatement>, bsc::IStatementFileProcessor::StatementLines) const = 0;
};

} // namespace bsc

#endif // #ifndef I_STATEMENT_PROCESSOR_H
