#include <string>

#include "bank_statement_converter/interfaces/i_transaction.h"

class ITransactionFormatter {
public:
    virtual std::string format(const ITransaction&) const = 0;
};