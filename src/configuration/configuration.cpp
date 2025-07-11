#include <fstream>

#include <rk_logger/logger.h>
#include <bank_statement_converter/configuration/configuration.h>

void Configuration::readConfigFile(const std::filesystem::path& path) {
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
    if (configNode && configNode.IsMap()) {
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
    } else {
        RK_LOG("Config section not found or invalid, using default settings");
    }

    RK_LOG("Config file read successfully\n");
}