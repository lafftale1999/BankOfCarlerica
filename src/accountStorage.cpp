#include "../include/accountStorage.h"
#include <string>
#include <fstream>
#include <chrono>

AccountStorage::AccountStorage(){}

AccountStorage::AccountStorage(int accountLimit)
{
    this->accountLimit = accountLimit;
    loadAccountsFromFile();

    if(accounts.size() > 0)
    {
        padding = accounts["00000000"].getAccountNumber().length();
    }
    else
    {
        padding = std::to_string(accountLimit).length();
    }
}

AccountStorage::~AccountStorage()
{
    writeAccountsToFile();
}

std::string AccountStorage::createNewAccount()
{
    if(accounts.size() >= (size_t)accountLimit) return "";

    std::string accountNumber = std::to_string(this->accounts.size());
    accountNumber = std::string(padding - std::to_string(this->accounts.size()).length(), '0') + std::to_string(this->accounts.size());

    accounts[accountNumber] = Account(accountNumber);

    return accountNumber;
}

void AccountStorage::addAccount(std::string accountNumber, std::string balance)
{
    accounts[accountNumber] = Account(accountNumber, balance);
}

void AccountStorage::removeAccount(std::string accountNumber)
{
    this->accounts[accountNumber].~Account();
}

Account* AccountStorage::findAccount(std::string accountNumber)
{
    auto it = accounts.find(accountNumber);

    if(it != accounts.end())
    {
        return &it->second;
    }

    return nullptr;
}

void AccountStorage::loadAccountsFromFile()
{   
    std::cout << "LOADING ACCOUNTS FROM FILE" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream file(ACCOUNTS_PATH);
   
    if(!file.is_open())
    {
        std::cout << "File was not found: " << ACCOUNTS_PATH << std::endl;
        return;
    }

    int counter = 0;
    std::string temp;
    std::vector<std::string>accountInformation(2);
    // [0] == ID
    // [1] == BALANCE

    int index = 0;

    while(std::getline(file, temp))
    {   
        if(counter > accountLimit)
        {
            std::cout << "Account limit has been reached while reading from file" << std::endl;
            return;
        }

        accountInformation[0] = "";
        accountInformation[1] = "";

        for(size_t i = 0; i < temp.length(); i++)
        {
            if(temp[i] == ',')
            {
                index++;
                continue;
            }

            accountInformation[index].push_back(temp[i]);
        }

        addAccount(accountInformation[0], accountInformation[1]);

        index = 0;
        counter++;
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Loading from file took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
}

void AccountStorage::writeAccountsToFile()
{
    std::cout << "WRITING ACCOUNTS TO FILE" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream file(ACCOUNTS_PATH);

    if(!file.is_open())
    {
        std::cout << "Unable to open file: " << ACCOUNTS_PATH << std::endl;
        return;
    }

    for(auto a : accounts)
    {
        if(a.second.getAccountNumber().empty()) continue;
        file << a.second.getAccountNumber() << "," << a.second.getBalance() << std::endl;
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Writing to file took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
}

std::map<std::string,Account> AccountStorage::getMap()
{
    return this->accounts;
}

int AccountStorage::getAccountLimit()
{
    return this->accountLimit;
}

int AccountStorage::getPadding()
{
    return this->padding;
}