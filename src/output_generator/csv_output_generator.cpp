#include <bank_statement_converter/output_generator/csv_output_generator.h>
#include <bank_statement_converter/transaction/transaction_adapter.h>
#include <rk_logger/logger.h>

namespace bsc {

void CsvOutputGenerator::generate(const std::vector<std::shared_ptr<IStatement>>& statements, std::filesystem::path& outputPath) {
    RK_LOG("Generating CSV output\n");

    if (statements.empty()) {
        RK_LOG("No statements provided for CSV generation\n");
        return;
    }
    if (!outputPath.has_extension()) {
        RK_LOG("Output file does not have an extension, adding .csv\n");
        outputPath += ".csv";
    } else if (outputPath.extension() != "csv") {
        outputPath.replace_extension("csv");
        RK_LOG("Output file extension changed to .csv\n");
    }

    if (std::filesystem::is_directory(outputPath)) {
        RK_LOG("Output path is a directory, appending default file name 'output.csv'\n");
        outputPath /= "output.csv";
    }

    RK_LOG("Output file path: %s\n", outputPath.string().c_str());
    std::ofstream outFile(outputPath);
    if (!outFile) {
        RK_LOG("Unable to open output file for CSV generation\n");
        return;
    }

    for (const auto& statement : statements) {
        for (const auto& transaction : statement->getTransactions()) {
            outFile << bsc::TransactionAdapter::toCsv(transaction) << "\n";
        }
    }
}

} // namespace bsc
