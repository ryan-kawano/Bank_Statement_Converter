#include <fstream>

#include <rk_logger/logger.h>
#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/configuration/configuration.h>

namespace bsc {

void Configuration::readConfigFile(const std::filesystem::path& path) {
    /* Verify that the config file is valid */
    if (path.empty()) {
        RK_LOG("Path was empty\n");
        return;
    }

    RK_LOG("Reading config file from path: ", path.string(), "\n");

    if (!std::filesystem::exists(path)) {
        RK_LOG("Config file not found at path: ", path.string(), ". Using default settings\n");
        return;
    }

    YAML::Node config = YAML::LoadFile(path.string());
    if (!config) {
        RK_LOG("Unable to read config file. Using default settings\n");
        return;
    }

    YAML::Node configNode = config["config"];
    if (!configNode || !configNode.IsMap()) {
        RK_LOG("Error reading config node\n");
        return;
    }

    /* Read and save values from the config */
    if (configNode["statements_directory"].IsDefined()) {
        statementsDirectory = configNode["statements_directory"].as<std::string>();
    } else {
        RK_LOG("statements_directory not found in config, using default");
    }
    
    if (configNode["statement_file_formats"].IsDefined()) {
        statementFileFormats.clear();
        for (const auto& format : configNode["statement_file_formats"]) {
            statementFileFormats.insert(format.as<std::string>());
        }
    } else {
        RK_LOG("statement_file_formats not found in config, using default");
    }
    
    if (configNode["output_formats"].IsDefined()) {
        outputFormats.clear();
        for (const auto& format : configNode["output_formats"]) {
            outputFormats.insert(format.as<std::string>());
        }
    } else {
        RK_LOG("output_formats not found in config, using default");
    }
    
    if (configNode["banks"].IsDefined()) {
        banks.clear();
        for (const auto& bank : configNode["banks"]) {
            if (bsc::constants::BANKS.count(bank.as<std::string>()) == 0) {
                RK_LOG("Unsupported bank found in config: ", bank.as<std::string>(), "\n");
            }
            banks.insert(bank.as<std::string>());
        }
    } else {
        RK_LOG("banks not found in config, using default");
    }
    
    if (configNode["output_one_file"].IsDefined()) {
        outputOneFile = configNode["output_one_file"].as<bool>();
    } else {
        RK_LOG("output_one_file not found in config, using default");
    }

    RK_LOG("Config file read successfully\n");
}

} // namespace bsc
