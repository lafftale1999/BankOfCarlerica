#ifndef ACCOUNT_STORAGE_H
#define ACCOUNT_STORAGE_H

#include "account.h"
#include <vector>

class AccountStorage
{
    std::vector<Account> accounts;
    int accountCounter;
    int accountLimit;

public:
    AccountStorage();
    void addAccount();
    void removeAccount(std::string accountNumber);
    Account* findAccount(std::string accountNumber);

    void readAccountsFromFile();
    void writeAccountsToFile();
};

#endif