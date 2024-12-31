#include "../include/bank.h"

Bank::Bank(){}

Bank::Bank(int size)
{
    accounts = AccountStorage(size * 3);
    clients = ClientStorage(size);
}

AccountStorage* Bank::getAccounts()
{
    return &this->accounts;
}

ClientStorage* Bank::getClients()
{
    return &this->clients;
}

TransactionLink* Bank::getTransactionLink()
{
    return &this->ts;
}