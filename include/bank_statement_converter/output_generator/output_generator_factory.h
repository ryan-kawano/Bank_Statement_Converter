#ifndef OUTPUT_GENERATOR_FACTORY_H
#define OUTPUT_GENERATOR_FACTORY_H

#include <memory>

#include <bank_statement_converter/output_generator/csv_output_generator.h>
#include <bank_statement_converter/interfaces/i_statement_output_generator.h>
#include <bank_statement_converter/output_generator/output_types.h>

namespace bsc {

class OutputGeneratorFactory {
public:

    /**
     * @brief Creates output generator instances based on the desired file type.
     * 
     * @param format The desired file format.
     * @return The created output generator.
     */
    static std::unique_ptr<IStatementOutputGenerator> createOutputGenerator(const bsc::output::Format format) {
        switch (format) {
            case bsc::output::Format::CSV:
                return std::make_unique<CsvOutputGenerator>();
            default:
                throw std::invalid_argument("Unsupported FileType");
        }
    }
};

} // namespace bsc

#endif // #ifndef OUTPUT_GENERATOR_FACTORY_H
