#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <filesystem>
#include <unordered_set>
#include <string>

#include <rk_logger/logger.h>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/convert.h>

namespace bsc {

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

    /**
     * @brief Reads the config file at the provided path and updates the internal values.
     * 
     * @param std::filesystem::path The path to the config file including the filename and extension.
     */
    void readConfigFile(const std::filesystem::path& path = std::filesystem::path(std::string(BANK_STATEMENT_CONVERTER_BINARY_DIRECTORY) + "/config.yaml"));

private:
    Configuration() = default;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    /* The values below have default values. They can be set via the config file */
    std::filesystem::path statementsDirectory = std::filesystem::current_path() / "statements";
    std::unordered_set<std::string> statementFileFormats = { "pdf" };
    std::unordered_set<std::string> outputFormats = { "csv" };
    bool outputOneFile = true;
    std::unordered_set<std::string> banks = { "Wells Fargo" };
};

} // namespace bsc

#endif // #ifndef CONFIGURATION_H
