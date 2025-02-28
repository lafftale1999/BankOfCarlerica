#ifndef TRANSACTION_STORAGE_H
#define TRANSACTION_STORAGE_H

#include "transaction.h"
#include "cache.h"
#include <vector>

#define TRANSACTIONS_PATH "data/transactions/transactions.txt"

class TransactionLink
{
    std::vector<Transaction> currentTransactions;
    static int transactionCount;
    static int transactionLimit;
    static int padding;
    static CacheLRU<Transaction,10> transactionCache;

public:
    TransactionLink();
    TransactionLink(int transactionLimit);
    TransactionLink(std::string accountNumber);

    void init();

    void addTransaction(std::string amount, std::string accountNumber);
    std::vector<Transaction> getTransactions(std::string accountNumber);
    Transaction getTransaction(std::string transactionID);
    Transaction formatTransaction(std::string unformattedString);
    std::vector<Transaction> getCurrentTransactions();
    void readTransactionsFromFile();
    void writeTransactionToFile(Transaction& transaction);
    void readFirstLine();
    int getPadding();
    int getTransactionLimit();
};

#endif