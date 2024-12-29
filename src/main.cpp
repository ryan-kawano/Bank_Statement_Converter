/**
 * @file main.cpp
 * @brief See the README.md file for an overview.
 */
#include <thread>
#include <chrono>
#include <filesystem>
#include "logger/log.h"
#include "pdf_processor.h"
#include "exception_rk.h"
#include "constants.h"
#include "quick_sort.h"

LOG_SETUP

int main() {
    LOG_VERIFY
    std::thread logThread = rk::log::startLogThread();
    const std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    LOG("Starting program\n");

    try {         
        if (!std::filesystem::exists(constants::OUTPUT_DIRECTORY)) {
            std::filesystem::create_directory(constants::OUTPUT_DIRECTORY);
        }
        
        PdfProcessor pdfProcessor;
        pdfProcessor.gatherPdfFiles("./" + constants::PDF_DIRECTORY);
        pdfProcessor.closeSkippedFilesFile();
 
        pdfProcessor.processPdfs("./" + constants::PDF_DIRECTORY);
        pdfProcessor.closeSkippedLinesFile();

        pdfProcessor.sortTransactions();
        pdfProcessor.printAllTransactions();
   
        pdfProcessor.generateCsvFile(constants::CSV_FILE_NAME);
    }
    catch (const Exception& e) {
        LOG("Caught exception: \"", e.what(), "\"\n");
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        auto duration = endTime - startTime;
        LOG("Exiting due to exception. Program took: ", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.0, " sec\n");
        rk::log::endLogThread(logThread);
        rk::log::closeLogFile();
    }
    catch (const std::filesystem::filesystem_error& e) {
        LOG("Caught exception: \"", e.what(), "\"\n");
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        auto duration = endTime - startTime;
        LOG("Exiting due to exception. Program took: ", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.0, " sec\n");
        rk::log::endLogThread(logThread);
        rk::log::closeLogFile();
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    auto duration = endTime - startTime;
    LOG("Finished successfully. Program took: ", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.0, " sec\n");

    rk::log::endLogThread(logThread);
    rk::log::closeLogFile();
    return 0;
}
