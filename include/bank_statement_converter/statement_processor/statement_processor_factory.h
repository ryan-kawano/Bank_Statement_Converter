#ifndef STATEMENT_PROCESSOR_FACTORY_H
#define STATEMENT_PROCESSOR_FACTORY_H
#include <memory>

#include <bank_statement_converter/interfaces/i_statement_processor.h>
#include <bank_statement_converter/statement/statement_file_format.h>

class StatementProcessorFactory {
public:
    std::unique_ptr<IStatementProcessor> createProcessor(StatementFileFormat::Format) const;
};

#endif // #ifndef STATEMENT_PROCESSOR_FACTORY_H
