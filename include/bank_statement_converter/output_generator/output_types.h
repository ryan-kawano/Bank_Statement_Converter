#ifndef OUTPUT_TYPES_H
#define OUTPUT_TYPES_H

#include <unordered_map>

namespace bsc {
namespace output {
    enum class Format {
        CSV = 0,
        TXT,
        XLSX
    };

    extern const std::unordered_map<std::string, Format> FORMAT_MAP;
} // namespace output
} // namespace bsc

#endif // #ifndef OUTPUT_TYPES_H
