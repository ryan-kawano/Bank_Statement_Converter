#ifndef STATEMENT_PROCESSOR_FACTORY_H
#define STATEMENT_PROCESSOR_FACTORY_H

#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/interfaces/i_statement_processor.h>
#include <bank_statement_converter/statement_processor/wells_fargo_statement_processor.h>

namespace bsc {

class StatementProcessorFactory {
public:
    static std::unique_ptr<IStatementProcessor> createStatementProcessor(const bsc::constants::Bank bank) {
        switch (bank) {
            case bsc::constants::Bank::WELLS_FARGO:
                return std::make_unique<WellsFargoStatementProcessor>();
            default:
                throw std::invalid_argument("Unsupported bank type");
        }
    }
};

} // namespace bsc

#endif // #ifndef STATEMENT_PROCESSOR_FACTORY_H
