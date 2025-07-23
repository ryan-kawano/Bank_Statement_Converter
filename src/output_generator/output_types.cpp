#include <string>

#include <bank_statement_converter/output_generator/output_types.h>

namespace bsc {
namespace output {

    const std::unordered_map<std::string, Format> FORMAT_MAP = {
        { std::string("csv"), Format::CSV },
        { std::string("txt"), Format::TXT },
        { std::string("xlsx"), Format::XLSX }
    };

} // namespace output
} // namespace bsc
