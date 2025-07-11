#ifndef CSV_OUTPUT_GENERATOR_H
#define CSV_OUTPUT_GENERATOR_H

#include <bank_statement_converter/interfaces/i_statement_output_generator.h>

class CsvOutputGenerator : public IStatementOutputGenerator {
public:
    void generate(const std::vector<std::shared_ptr<IStatement>>& data, const std::filesystem::path& outputPath) override;
};

#endif // #ifndef CSV_OUTPUT_GENERATOR_H
