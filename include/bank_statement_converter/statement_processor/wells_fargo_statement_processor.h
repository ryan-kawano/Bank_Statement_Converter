#ifndef WELLS_FARGO_STATEMENT_PROCESSOR_H
#define WELLS_FARGO_STATEMENT_PROCESSOR_H

#include <bank_statement_converter/interfaces/i_statement_processor.h>

namespace bsc {

class WellsFargoStatementProcessor : public IStatementProcessor {
    /**
     * @brief Processes lines of a Wells Fargo statement.
     * 
     * @param statement Statement object to populate.
     * @param lines Container of lines from the statement.
     */
    void processLines(std::shared_ptr<IStatement> statement, IStatementFileProcessor::StatementLines lines) const override;
};

} // namespace bsc

#endif // #ifndef WELLS_FARGO_STATEMENT_PROCESSOR_H
