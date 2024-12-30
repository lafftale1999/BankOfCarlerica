#ifndef ACCOUNT_STORAGE_H
#define ACCOUNT_STORAGE_H

#include "account.h"
#include <vector>
#include <map>

#define ACCOUNTS_PATH "data/accounts/accounts.txt"

class AccountStorage
{
    std::map<std::string,Account> accounts;
    int accountLimit;

public:
    AccountStorage(int accountLimit);
    ~AccountStorage();
    void addAccount(std::string accountNumber, std::string balance);
    void createAccount();
    void removeAccount(std::string accountNumber);
    Account& findAccount(std::string accountNumber);

    void loadAccountsFromFile();
    void writeAccountsToFile();

    std::map<std::string,Account> getMap();
};

#endif