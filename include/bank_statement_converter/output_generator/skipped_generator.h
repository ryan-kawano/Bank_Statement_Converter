#ifndef SKIPPED_GENERATOR_H
#define SKIPPED_GENERATOR_H

#include <vector>
#include <fstream>

#include <rk_logger/logger.h>

namespace bsc {

/**
 * @brief Generates a file that contains items that were skipped during execution.
 * 
 * @param skipped Container holding the skipped items.
 * @param type The type of skipped item, e.g., skipped files, skipped lines, etc.
 */
template<typename T>
void generateSkippedFile(const std::vector<T> skipped, const std::string& type) {
    const std::string fileName = std::string("skipped_") + type + ".txt";

    RK_LOG("Creating skipped file: ", fileName, "\n");
    std::ofstream outFile(fileName);

    if (!outFile) {
        RK_LOG("Unable to open skipped file for output\n");
        return;
    }

    if (skipped.empty()) {
        outFile << "No skipped " << type << "\n";
    }

    for (const auto& item : skipped) {
        outFile << item << std::endl;
    }

    outFile.close();
    RK_LOG("Successfully created skipped file: ", fileName, "\n");
}

} // namespace bsc

#endif // #ifndef SKIPPED_GENERATOR_H
