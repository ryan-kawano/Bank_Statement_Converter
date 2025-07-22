#include <bank_statement_converter/statement/statement_file_format.h>

namespace bsc {
namespace statement_file_format {

    const std::unordered_map<std::string, Format> FORMAT_MAP = {
        { ".pdf", Format::PDF },
        { ".txt", Format::TXT },
        { ".xlsx", Format::XLSX }
    };

} // namespace statement_file_format
} // namespace bsc
