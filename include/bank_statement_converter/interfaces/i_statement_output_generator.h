#ifndef I_STATEMENT_OUTPUT_GENERATOR_H
#define I_STATEMENT_OUTPUT_GENERATOR_H

#include <vector>
#include <memory>
#include <filesystem>

#include <bank_statement_converter/interfaces/i_statement.h>

namespace bsc {

class IStatementOutputGenerator {
public:
    virtual ~IStatementOutputGenerator() = default;
    virtual void generate(const std::vector<std::shared_ptr<IStatement>>&, const std::filesystem::path&) = 0;
};

} // namespace bsc

#endif // #ifndef I_STATEMENT_OUTPUT_GENERATOR_H
