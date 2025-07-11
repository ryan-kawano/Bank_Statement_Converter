#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <filesystem>
#include <unordered_set>
#include <string>

#include <rk_logger/logger.h>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/convert.h>

class Configuration {
public:
    static Configuration& instance() {
        static Configuration instance;
        return instance;
    }

    const std::filesystem::path& getStatementsDirectory() const { return statementsDirectory; }
    const std::unordered_set<std::string>& getStatementFileFormats() const { return statementFileFormats; }
    const std::unordered_set<std::string>& getOutputFormats() const { return outputFormats; }
    bool getOutputOneFile() const { return outputOneFile; }
    const std::unordered_set<std::string>& getBanks() const { return banks; }

    void readConfigFile(const std::filesystem::path& path = std::filesystem::path(std::string(BANK_STATEMENT_CONVERTER_BINARY_DIRECTORY) + "/config.yaml"));

private:
    Configuration() = default;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    std::filesystem::path statementsDirectory = "./statements";
    std::unordered_set<std::string> statementFileFormats = { "pdf" };
    std::unordered_set<std::string> outputFormats = { "csv" };
    bool outputOneFile = true;
    std::unordered_set<std::string> banks = { "Wells Fargo" };
};

#endif // #ifndef CONFIGURATION_H
