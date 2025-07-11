#include <bank_statement_converter/output_generator/output_types.h>

namespace Output {
    const std::unordered_map<std::string, Format> FORMAT_MAP = {
        { "csv", Format::CSV },
        { "txt", Format::TXT },
        { "xlsx", Format::XLSX }
    };
} // namespace Output
