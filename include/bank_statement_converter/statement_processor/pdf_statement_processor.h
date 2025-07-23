#ifndef PDF_STATEMENT_PROCESSOR_H
#define PDF_STATEMENT_PROCESSOR_H

#include <string>
#include <fstream>

#include <fpdfview.h>
#include <fpdf_text.h>

#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/interfaces/i_statement_file_processor.h>
#include <bank_statement_converter/statement/statement_file_format.h>

namespace bsc {

/**
 * @class PdfStatementProcessor
 * @brief Responsible for processing statements in PDF format.
 */
class PdfStatementProcessor : public IStatementFileProcessor {
public:
    /**
     * @brief Processes a PDF statement file and returns a corresponding statement object.
     * 
     * @param path The path to the statement file.
     * @return The created IStatement object.
     */
    std::shared_ptr<IStatement> processFile(const std::filesystem::path& path) override;

private:
    FPDF_DOCUMENT openFile(const std::filesystem::path&) const;
};

} // namespace bsc

#endif // #ifndef PDF_STATEMENT_PROCESSOR_H
