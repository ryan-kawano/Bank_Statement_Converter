#ifndef WELLS_FARGO_STATEMENT_PROCESSOR_H
#define WELLS_FARGO_STATEMENT_PROCESSOR_H

#include <bank_statement_converter/interfaces/i_statement_processor.h>

namespace bsc {

class WellsFargoStatementProcessor : public IStatementProcessor {
    void processLines(std::shared_ptr<IStatement>, IStatementFileProcessor::StatementLines) const override;
};

} // namespace bsc

#endif // #ifndef WELLS_FARGO_STATEMENT_PROCESSOR_H
