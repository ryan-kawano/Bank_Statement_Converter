#ifndef STATEMENT_FILE_MANAGER_H
#define STATEMENT_FILE_MANAGER_H

#include <filesystem>

#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/statement/statement_file_format.h>

namespace bsc {

/**
 * @class StatementFileManager
 * @brief Responsible for handling statements at the file-level.
 * 
 * Responsible for handling statements as they exist on a file system.
 */
class StatementFileManager {
public:
    using File = std::pair<std::filesystem::path, bsc::statement_file_format::Format>;
    
    /**
     * @brief Looks through a directory and saves any statement files that are present.
     * 
     * @param statementFilesPath Path to look through.
     * @param fileFormats Accepted file formats.
     */
    void gatherFiles(const std::filesystem::path& statementFilesPath, const std::unordered_set<std::string>& fileFormats);

    /**
     * @brief Gets the container of files that were skipped during the gathering process.
     * 
     * @return Container of skipped files.
     */
    const std::vector<std::filesystem::path> getskippedFiles() const;

    const std::vector<File>& getFiles() const;
    void reset();

private:
    std::vector<File> files;
    std::vector<std::filesystem::path> skippedFiles;
};

} // namespace bsc

#endif // #ifndef STATEMENT_FILE_MANAGER_H
