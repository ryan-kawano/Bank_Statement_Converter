#ifndef STATEMENT_FILE_PROCESSOR_FACTORY_H
#define STATEMENT_FILE_PROCESSOR_FACTORY_H
#include <memory>

#include <bank_statement_converter/interfaces/i_statement_file_processor.h>
#include <bank_statement_converter/statement/statement_file_format.h>

namespace bsc {

/**
 * @class StatementFileProcessorFactory
 * @brief Generates objects that process statements at the file-level.
 */
class StatementFileProcessorFactory {
public:
    /**
     * @brief Creates and returns a processor for a given file type.
     * 
     * @param format Target file format to process.
     * @return Instance of a file processor for the given type.
     */
    static std::unique_ptr<IStatementFileProcessor> createProcessor(const bsc::statement_file_format::Format format) {
        switch (format) {
            // case statement_file_format::Format::PDF:
            //     return std::make_unique<CSVStatementProcessor>();
            case bsc::statement_file_format::Format::PDF:
                return std::make_unique<PdfStatementProcessor>();
            // case statement_file_format::Format::XLSX:
            //     return std::make_unique<XLSXStatementProcessor>();
            default:
                throw std::invalid_argument("Unsupported FileType");
        }
    }
};

} // namespace bsc

#endif // #ifndef STATEMENT_FILE_PROCESSOR_FACTORY_H
