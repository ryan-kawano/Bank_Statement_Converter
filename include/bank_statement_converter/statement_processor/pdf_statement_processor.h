#ifndef PDF_PROCESSOR_H
#define PDF_PROCESSOR_H

#include <string>
#include <fstream>

#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/interfaces/i_statement_processor.h>
#include <bank_statement_converter/statement/statement_file_format.h>

class PdfStatementProcessor : public IStatementProcessor {
public:
    std::shared_ptr<IStatement> processFile(const std::filesystem::path&) override;

private:
    void openFile(const std::filesystem::path&) const override;
};

#endif // #if PDF_PROCESSOR_H
