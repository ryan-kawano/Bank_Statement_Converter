/**
 * @file main.cpp
 * @brief See the README.md file for an overview.
 */
#include <thread>
#include <chrono>
#include <filesystem>
#include "rk_logger/logger.h"
#include <bank_statement_converter/statement/statement_file_manager.h>
#include <bank_statement_converter/statement/statement_manager.h>
#include <bank_statement_converter/exception_rk.h>
#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/output_generator/output_generator_factory.h>
#include <bank_statement_converter/interfaces/i_statement_output_generator.h>
#include <bank_statement_converter/output_generator/skipped_generator.h>
#include <bank_statement_converter/configuration/configuration.h>

int main() {
    std::thread logThread = rk::log::startLogger();
    const std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    RK_LOG("Starting \"Bank Statement Converter\"\n");
    StatementFileManager statementFileMgr;
    StatementManager statementMgr;
    OutputGeneratorFactory outputGenFactory;

    Configuration::instance().readConfigFile();
    auto& config = Configuration::instance();

    try {
        if (!std::filesystem::exists(constants::OUTPUT_DIRECTORY)) {
            std::filesystem::create_directory(constants::OUTPUT_DIRECTORY);
        }

        statementFileMgr.gatherFiles(config.getStatementsDirectory(), config.getStatementFileFormats());
        statementMgr.parseStatements(statementFileMgr.getFiles());
        statementMgr.sort();
   
        for (const auto& outputFormat : config.getOutputFormats()) {
            const auto iter = Output::FORMAT_MAP.find(outputFormat);
            if (iter != Output::FORMAT_MAP.end()) {
                std::unique_ptr<IStatementOutputGenerator> generator = outputGenFactory.createOutputGenerator(iter->second);
                generator->generate(statementMgr.getStatements(), std::filesystem::path(constants::OUTPUT_DIRECTORY)/"output");
            }
        }

        generateSkippedFile(statementFileMgr.getskippedFiles(), "skipped_files");
        generateSkippedFile(statementMgr.getSkippedLines(), "skipped_lines");
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
    RK_LOG("Finished successfully. Processed ", statementMgr.getCount(), " transactions in ", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.0, " sec\n");

    rk::log::stopLogger(std::move(logThread));

    return 0;
}
