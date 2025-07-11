#ifndef OUTPUT_GENERATOR_FACTORY_H
#define OUTPUT_GENERATOR_FACTORY_H

#include <memory>

#include <bank_statement_converter/interfaces/i_statement_output_generator.h>
#include <bank_statement_converter/output_generator/output_types.h>

class OutputGeneratorFactory {
public:
    std::unique_ptr<IStatementOutputGenerator> createOutputGenerator(const Output::Format format) const;
};

#endif // #ifndef OUTPUT_GENERATOR_FACTORY_H
