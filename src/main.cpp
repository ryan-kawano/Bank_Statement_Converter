/**
 * @file main.cpp
 * @brief See the README.md file for an overview.
 */
#include <thread>
#include <chrono>
#include <filesystem>
#include "rk_logger/logger.h"
#include "wells_fargo_statement_converter/pdf_processor.h"
#include "wells_fargo_statement_converter/exception_rk.h"
#include "wells_fargo_statement_converter/constants.h"
#include "wells_fargo_statement_converter/quick_sort.h"

int main() {
    std::thread logThread = rk::log::startLogger();
    const std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    RK_LOG("Starting \"Wells Fargo Statement PDF to CSV Converter\"\n");

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
        RK_LOG("Caught exception: \"", e.what(), "\"\n");
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        auto duration = endTime - startTime;
        // duration_cast to milliseconds instead of seconds to preserve fractional portion
        RK_LOG("Exiting due to exception. Program took: ", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.0, " sec\n");
        rk::log::stopLogger(std::move(logThread));
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    auto duration = endTime - startTime;
    // duration_cast to milliseconds instead of seconds to preserve fractional portion
    RK_LOG("Finished successfully. Program took: ", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.0, " sec\n");

    rk::log::stopLogger(std::move(logThread));

    return 0;
}
