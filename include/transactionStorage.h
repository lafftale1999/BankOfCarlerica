#ifndef TRANSACTION_STORAGE_H
#define TRANSACTION_STORAGE_H

#include "transaction.h"
#include <vector>

#define TRANSACTIONS_PATH "data/transactions/transactions.txt"

class TransactionStorage
{
    std::vector<Transaction> transactions;
    static int transactionCount;
    // CacheLRU

public:
    TransactionStorage();
    void addTransaction(float amount, std::string accountNumber);
    void addTransaction(std::string unformattedString);
    std::vector<Transaction>& getTransactions();
    std::vector<Transaction*> getTransactions(std::string accountNumber);
    Transaction* getTransaction(std::string transactionID);

    void readTransactionsFromFile();
    void writeTransactionsToFile();
};

#endif