#ifndef MY_BANK_H
#define MY_BANK_H

#include "accountStorage.h"
#include "clientStorage.h"
#include "transactionLink.h"
#include "bankQueue.h"

class Bank
{
    AccountStorage accounts;
    ClientStorage clients;
    TransactionLink transactionLink;
    // BankQueue<std::string, 10> queue;

    Client* currentClient;

public:
    Bank();
    Bank(int size);

    AccountStorage* getAccounts();
    ClientStorage* getClients();
    TransactionLink* getTransactionLink();
    
    void setCurrentClient(std::string client);
    void setNextClient();
    Client* getCurrentClient();
    BankQueue<std::string, 10>& getQueue();
};

#endif