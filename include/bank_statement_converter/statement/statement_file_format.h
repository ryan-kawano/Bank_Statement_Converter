#ifndef STATEMENT_FILE_FORMAT_H
#define STATEMENT_FILE_FORMAT_H

#include <unordered_map>

namespace StatementFileFormat {
    enum class Format {
        PDF = 0,
        TXT,
        XLSX
    };

    extern const std::unordered_map<std::string, Format> FORMAT_MAP;
} // namespace StatementFileFormat

#endif // #ifndef STATEMENT_FILE_FORMAT_H
