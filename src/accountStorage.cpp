#include "../include/accountStorage.h"
#include <string>
#include <fstream>
#include <chrono>

AccountStorage::AccountStorage(int accountLimit)
{
    this->accountLimit = accountLimit;
    loadAccountsFromFile();
}

AccountStorage::~AccountStorage()
{
    writeAccountsToFile();
}

void AccountStorage::createAccount()
{
    if(accounts.size() >= (size_t)accountLimit) throw "AccountStorage is full";

    std::string accountNumber = std::to_string(this->accounts.size());
    accountNumber = std::string(std::to_string(accountLimit).length() - std::to_string(this->accounts.size()).length(), '0') + std::to_string(this->accounts.size());

    accounts[accountNumber] = Account(accountNumber);
}

void AccountStorage::addAccount(std::string accountNumber, std::string balance)
{
    accounts[accountNumber] = Account(accountNumber, balance);
}

void AccountStorage::removeAccount(std::string accountNumber)
{
    this->accounts[accountNumber].~Account();
}

Account& AccountStorage::findAccount(std::string accountNumber)
{
    return this->accounts[accountNumber];
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
    std::cout << "WRITING TO FILE" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream file(ACCOUNTS_PATH);

    if(!file.is_open())
    {
        std::cout << "Unable to open file: " << ACCOUNTS_PATH << std::endl;
        return;
    }

    for(auto a : accounts)
    {
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