#include "../include/accountStorage.h"

AccountStorage::AccountStorage()
{
    accountCounter = 0;

    accountLimit = 10000000;
}

void AccountStorage::addAccount()
{
    std::string accountNumber = 
    accounts.emplace_back()
}
void removeAccount(std::string accountNumber);
Account* findAccount(std::string accountNumber);

void readAccountsFromFile();
void writeAccountsToFile();