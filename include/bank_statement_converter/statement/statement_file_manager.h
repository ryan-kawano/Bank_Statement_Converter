#ifndef STATEMENT_FILE_MANAGER_H
#define STATEMENT_FILE_MANAGER_H

#include <filesystem>

#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/statement/statement_file_format.h>

namespace bsc {

class StatementFileManager {
public:
    using File = std::pair<std::filesystem::path, bsc::statement_file_format::Format>;
    
    void gatherFiles(const std::filesystem::path&, const std::unordered_set<std::string>&);
    const std::vector<File>& getFiles() const;
    const std::vector<std::filesystem::path> getskippedFiles() const;
    void reset();

private:
    std::vector<File> files;
    std::vector<std::filesystem::path> skippedFiles;
};

} // namespace bsc

#endif // #ifndef STATEMENT_FILE_MANAGER_H
