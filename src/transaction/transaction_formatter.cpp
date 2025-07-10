#include <sstream>
#include <iomanip>

#include "bank_statement_converter/transaction/transaction_formatter.h"

std::string CSVTransactionFormatter::format(const ITransaction& transaction) const {
    std::ostringstream oss;

    // Account Number
    oss << "\"" << transaction.getAccountNumber() << "\",";

    // Date
    oss << "\"";
    oss << std::setw(2) << std::setfill('0') << transaction.getDate().getMonth();
    oss << "/";
    oss << std::setw(2) << std::setfill('0') << transaction.getDate().getDay();
    oss << "/";
    oss << std::setw(4) << transaction.getDate().getYear();
    oss << "\",";

    // ID
    oss << "\"" << transaction.getId() << "\",";

    // Description
    oss << "\"" << transaction.getDescription() << "\",";

    // Amount
    oss << "\"";
    oss << std::fixed << std::setprecision(2) << transaction.getAmount();
    oss << "\"";

    return oss.str();
}