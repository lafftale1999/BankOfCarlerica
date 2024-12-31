#ifndef MY_BANK_H
#define MY_BANK_H

#include "accountStorage.h"
#include "clientStorage.h"
#include "transactionLink.h"

class Bank
{
    AccountStorage accounts;
    ClientStorage clients;
    TransactionLink ts;

public:
    Bank();
    Bank(int size);

    AccountStorage* getAccounts();
    ClientStorage* getClients();
    TransactionLink* getTransactionLink();
};

#endif