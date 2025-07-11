#include <bank_statement_converter/statement_processor/statement_processor_factory.h>
#include <bank_statement_converter/statement_processor/pdf_statement_processor.h>

std::unique_ptr<IStatementProcessor> StatementProcessorFactory::createProcessor(StatementFileFormat::Format format) const {
    switch (format) {
        // case StatementFileFormat::Format::PDF:
        //     return std::make_unique<CSVStatementProcessor>();
        case StatementFileFormat::Format::PDF:
            return std::make_unique<PdfStatementProcessor>();
        // case StatementFileFormat::Format::XLSX:
        //     return std::make_unique<XLSXStatementProcessor>();
        default:
            throw std::invalid_argument("Unsupported FileType");
    }
}
