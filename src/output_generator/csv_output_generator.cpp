#include <bank_statement_converter/output_generator/csv_output_generator.h>
#include <bank_statement_converter/transaction/transaction_adapter.h>
#include <rk_logger/logger.h>

namespace bsc {

void CsvOutputGenerator::generate(const std::vector<std::shared_ptr<IStatement>>& statements, const std::filesystem::path& outputPath) {
    RK_LOG("Generating CSV output\n");

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
