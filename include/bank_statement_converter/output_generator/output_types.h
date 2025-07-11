#ifndef OUTPUT_TYPES_H
#define OUTPUT_TYPES_H

#include <unordered_map>

namespace Output {
    enum class Format {
        CSV = 0,
        TXT,
        XLSX
    };

    extern const std::unordered_map<std::string, Format> FORMAT_MAP;
} // namespace Output

#endif // #ifndef OUTPUT_TYPES_H
