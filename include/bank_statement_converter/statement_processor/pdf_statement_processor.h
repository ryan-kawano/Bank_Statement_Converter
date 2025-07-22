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

class PdfStatementProcessor : public IStatementFileProcessor {
public:
    std::shared_ptr<IStatement> processFile(const std::filesystem::path&) override;

private:
    FPDF_DOCUMENT openFile(const std::filesystem::path&) const;
};

} // namespace bsc

#endif // #ifndef PDF_STATEMENT_PROCESSOR_H
