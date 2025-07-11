#include <bank_statement_converter/output_generator/csv_output_generator.h>

void CsvOutputGenerator::generate(const std::vector<std::shared_ptr<IStatement>>& data, const std::filesystem::path& outputPath) {
    RK_LOG("Generating CSV output\n");

    std::ofstream outFile(outputPath);

    if (!outFile) {
        RK_LOG("Unable to open output file for CSV generation\n");
        return;
    }
    /*
    TO DO
    */
}
