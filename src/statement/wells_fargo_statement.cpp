#include <bank_statement_converter/statement/wells_fargo_statement.h>
#include <bank_statement_converter/quick_sort.h>

std::filesystem::path WellsFargoStatement::getPath() const {
    return path;
}

const std::vector<std::shared_ptr<ITransaction>>& WellsFargoStatement::getTransactions() const {
    return transactions;
}

const Date& WellsFargoStatement::getDate() const {
    return date;
}

const WellsFargoStatement::SkippedLines& WellsFargoStatement::getSkippedLines() const {
    return skippedLines;
}

void WellsFargoStatement::setPath(std::filesystem::path& path) {
    this->path = path;
}

void WellsFargoStatement::setDate(const Date& date) {
    this->date = date;
}

void WellsFargoStatement::addTransaction(std::shared_ptr<ITransaction> transaction) {
    transactions.push_back(transaction);
}

void WellsFargoStatement::addSkippedLine(const std::string& line) {
    skippedLines.push_back(line);
}

void WellsFargoStatement::sort() {
    QuickSort<ITransaction>::quickSort(transactions, 0, transactions.size());
}
