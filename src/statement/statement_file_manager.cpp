#include <rk_logger/logger.h>
#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/exception_rk.h>
#include <bank_statement_converter/statement/statement_file_manager.h>

namespace bsc {

void StatementFileManager::gatherFiles(const std::filesystem::path& statementFilesPath, const std::unordered_set<std::string>& fileFormats) {
    RK_LOG("Gathering statement files from directory: ", statementFilesPath, "\n");

    if (!std::filesystem::exists(statementFilesPath)) {
        const std::string errMessage = statementFilesPath.string() + " doesnt exist";
        RK_LOG(errMessage, "\n");
        throw Exception(errMessage);
    }
    if (fileFormats.empty()) {
        const std::string errMessage = "No statement file formats were provided";
        RK_LOG(errMessage, "\n");
        throw Exception(errMessage);
    }

    // Go through the files in the directory and add it to the list if it is a supported format.
    // Otherwise, add it to the skipped files.
    std::string fileName;
    for (const auto& entry : std::filesystem::directory_iterator(statementFilesPath)) {
        //fileName = file.path().filename().string();
        RK_LOG("Processing entry ", entry, "\n");

        if (entry.is_directory()) {
            RK_LOG("Entry ", entry, " is directory. Skipping\n");
            continue;
        }

        const auto iter = bsc::statement_file_format::FORMAT_MAP.find(entry.path().extension().string());
        if (iter == bsc::statement_file_format::FORMAT_MAP.end()) {
            RK_LOG("Entry ", entry, " doesn't have target file extension. Skipping\n");
            skippedFiles.push_back(entry);
            continue;
        }

        RK_LOG("Adding ", entry.path().filename().string(), " to statement files\n");
        files.push_back(std::make_pair(entry, iter->second));
    }

    RK_LOG("Finished gathering statement files. Found ", files.size(), " statement files. Skipped ", skippedFiles.size(), " files.\n");
}

const std::vector<StatementFileManager::File>& StatementFileManager::getFiles() const {
    return files;
}

const std::vector<std::filesystem::path> StatementFileManager::getskippedFiles() const {
    return skippedFiles;
}

void StatementFileManager::reset() {
    RK_LOG("Resetting StatementFileManager\n");
    files.clear();
    skippedFiles.clear();
}

} // namespace bsc
