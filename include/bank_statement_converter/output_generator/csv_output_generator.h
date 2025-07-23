#ifndef CSV_OUTPUT_GENERATOR_H
#define CSV_OUTPUT_GENERATOR_H

#include <bank_statement_converter/interfaces/i_statement_output_generator.h>

namespace bsc {

/**
 * @class CsvOutputGenerator
 * @brief Responsible for generating the final output in CSV format.
 */
class CsvOutputGenerator : public IStatementOutputGenerator {
public:
    /**
     * @brief Generates the final output file in CSV format.
     * 
     * @param statements The statements to be processed and written to the CSV file.
     * @param outputPath The path to output the file, including the file name with extension.
     */
    void generate(const std::vector<std::shared_ptr<IStatement>>& statements, std::filesystem::path& outputPath) override;
};

} // namespace bsc

#endif // #ifndef CSV_OUTPUT_GENERATOR_H
