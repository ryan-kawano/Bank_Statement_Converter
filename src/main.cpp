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
    RK_LOG("Starting \"Bank Statement Converter\"\n");
    const std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    bsc::StatementFileManager statementFileMgr;
    bsc::StatementManager statementMgr;

    RK_LOG("Reading config file\n");
    bsc::Configuration::instance().readConfigFile();
    auto& config = bsc::Configuration::instance();

    try {
        if (!std::filesystem::exists(bsc::constants::OUTPUT_DIRECTORY)) {
            std::filesystem::create_directory(bsc::constants::OUTPUT_DIRECTORY);
        }

        statementFileMgr.gatherFiles(config.getStatementsDirectory(), config.getStatementFileFormats());
        statementMgr.parseStatements(statementFileMgr.getFiles());
        statementMgr.sort();
   
        for (const auto& outputFormat : config.getOutputFormats()) {
            const auto iter = bsc::output::FORMAT_MAP.find(outputFormat);
            if (iter != bsc::output::FORMAT_MAP.end()) {
                std::unique_ptr<bsc::IStatementOutputGenerator> generator = bsc::OutputGeneratorFactory::createOutputGenerator(iter->second);
                generator->generate(statementMgr.getStatements(), (std::filesystem::path(bsc::constants::OUTPUT_DIRECTORY)/"output").replace_extension(std::string(".") + outputFormat));
            }
        }

        bsc::generateSkippedFile(statementFileMgr.getskippedFiles(), "skipped_files");
        bsc::generateSkippedFile(statementMgr.getSkippedLines(), "skipped_lines");
    }
    catch (const bsc::Exception& e) {
        RK_LOG("Caught exception: \"", e.what(), "\"\n");
        // duration_cast to milliseconds instead of seconds to preserve fractional portion
        RK_LOG("Exiting due to exception. Program took: ", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() / 1000.0, " sec\n");
        rk::log::stopLogger(std::move(logThread));
    }

    // duration_cast to milliseconds instead of seconds to preserve fractional portion
    RK_LOG("Finished successfully. Processed ", statementMgr.getCount(), " statements in ", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() / 1000.0, " sec\n");
    rk::log::stopLogger(std::move(logThread));

    return 0;
}
