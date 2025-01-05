#ifndef MY_BANK_H
#define MY_BANK_H

#include "accountStorage.h"
#include "clientStorage.h"
#include "transactionLink.h"
#include "bankQueue.h"

class Bank
{
    AccountStorage* accounts;
    ClientStorage* clients;
    TransactionLink* transactionLink;
    BankQueue<std::string, 10> queue;

    Client* currentClient;
    Transaction currentTransaction;
    Account* currentAccount;

public:
    Bank();
    Bank(AccountStorage* as, ClientStorage* cs, TransactionLink* ts);

    AccountStorage* getAccounts();
    ClientStorage* getClients();
    TransactionLink* getTransactionLink();
    
    void setCurrentClient(std::string clientID);
    void setCurrentTransaction(Transaction transaction);
    void setCurrentAccount(std::string accountNumber);
    Client* getCurrentClient();
    Transaction& getCurrentTransaction();
    Account* getCurrentAccount();

    void setNextClient();
    BankQueue<std::string, 10>& getQueue();
};

#endif