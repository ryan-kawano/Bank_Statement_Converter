#include <bank_statement_converter/output_generator/output_generator_factory.h>
#include <bank_statement_converter/output_generator/output_types.h>
#include <bank_statement_converter/output_generator/csv_output_generator.h>

std::unique_ptr<IStatementOutputGenerator> OutputGeneratorFactory::createOutputGenerator(const Output::Format format) const {
    switch (format) {
        case Output::Format::CSV:
            return std::make_unique<CsvOutputGenerator>();
        default:
            throw std::invalid_argument("Unsupported FileType");
    }
}
