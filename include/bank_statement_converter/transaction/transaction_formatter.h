#include "bank_statement_converter/interfaces/i_transaction_formatter.h"

class CSVTransactionFormatter : public ITransactionFormatter {
public:
    static CSVTransactionFormatter& instance() {
        static CSVTransactionFormatter instance;
        return instance;
    }
    std::string format(const ITransaction&) const override;

private:
    CSVTransactionFormatter() = default;
    CSVTransactionFormatter(const CSVTransactionFormatter&) = delete;
    CSVTransactionFormatter& operator=(const CSVTransactionFormatter&) = delete;
};