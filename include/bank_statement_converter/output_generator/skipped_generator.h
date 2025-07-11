#ifndef SKIPPED_GENERATOR_H
#define SKIPPED_GENERATOR_H

#include <vector>
#include <fstream>

#include <rk_logger/logger.h>

template<typename T>
void generateSkippedFile(const std::vector<T> skipped, const std::string& type) {
    const std::string fileName = std::string("skipped_") + type + ".txt";
    RK_LOG("Creating skipped file: ", fileName, "\n");
    std::ofstream outFile(fileName);

    if (!outFile) {
        RK_LOG("Unable to open skipped file for output\n");
        return;
    }

    for (const auto& item : skipped) {
        outFile << item << std::endl;
    }

    outFile.close();
    RK_LOG("Successfully created skipped file: ", fileName, "\n");
}

#endif // #ifndef SKIPPED_GENERATOR_H