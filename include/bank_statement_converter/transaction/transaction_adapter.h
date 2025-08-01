#ifndef TRANSACTION_ADAPTER_H
#define TRANSACTION_ADAPTER_H 

#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <bank_statement_converter/interfaces/i_transaction.h>

namespace bsc {

/**
 * @class TransactionAdapter
 * @brief Responsible for adapting transactions to various formats.
 */
class TransactionAdapter {
public:
    /**
     * @brief Processes a transaction and returns a copy in CSV format.
     * 
     * @param transaction The ITransaction object to convert.
     * @return The converted transaction as CSV text.
     */
    static std::string toCsv(const std::shared_ptr<ITransaction> transaction) {
        std::stringstream ss;
        ss << "\""
        << transaction->getAccountNumber() << "\",\""
        << std::setw(2) << std::setfill('0') << transaction->getDate().getMonth() << '/'
        << std::setw(2) << std::setfill('0') << transaction->getDate().getDay() << '/'
        << std::setw(4) << transaction->getDate().getYear() << "\","
        << "\"" << transaction->getId() << "\","
        << "\"" << transaction->getDescription() << "\","
        << "\"" << std::fixed << std::setprecision(2) << transaction->getAmount()
        << "\"";

        return ss.str();
    }
};

} // namespace bsc

#endif // #ifndef TRANSACTION_ADAPTER_H
