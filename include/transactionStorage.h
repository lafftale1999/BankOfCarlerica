#ifndef TRANSACTION_STORAGE_H
#define TRANSACTION_STORAGE_H

#include "transaction.h"
#include <vector>

#define TRANSACTIONS_PATH "data/transactions/transactions.txt"

class TransactionStorage
{
    std::vector<Transaction> transactions;
    int transactionCount;
    int transactionLimit;
    // CacheLRU

public:
    TransactionStorage();
    void addTransaction(std::string amount, std::string accountNumber);
    std::vector<Transaction> getTransactions(std::string accountNumber);
    Transaction getTransaction(std::string transactionID);
    Transaction formatTransaction(std::string unformattedString);
    void readTransactionsFromFile();
    void writeTransactionToFile(Transaction& transaction);
};

#endif