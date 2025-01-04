#include "../include/bank.h"

Bank::Bank(){}

Bank::Bank(AccountStorage* as, ClientStorage* cs, TransactionLink* ts)
{
    accounts = as;
    clients = cs;
    transactionLink = ts;
}

AccountStorage* Bank::getAccounts()
{
    return this->accounts;
}

ClientStorage* Bank::getClients()
{
    return this->clients;
}

TransactionLink* Bank::getTransactionLink()
{
    return this->transactionLink;
}

void Bank::setCurrentClient(std::string clientId)
{
    this->currentClient = this->clients->findClient(clientId);
}

Client* Bank::getCurrentClient()
{
    return currentClient;
}

void Bank::setNextClient()
{
    this->currentClient = this->clients->findClient(this->queue.dequeue());
}

BankQueue<std::string, 10>& Bank::getQueue()
{
    return queue;
}