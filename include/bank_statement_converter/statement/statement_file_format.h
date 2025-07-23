#ifndef STATEMENT_FILE_FORMAT_H
#define STATEMENT_FILE_FORMAT_H

#include <unordered_map>

namespace bsc {
namespace statement_file_format {

    enum class Format {
        PDF = 0,
        TXT,
        XLSX
    };

    extern const std::unordered_map<std::string, Format> FORMAT_MAP;

} // namespace statement_file_format
} // namespace bsc

#endif // #ifndef STATEMENT_FILE_FORMAT_H
