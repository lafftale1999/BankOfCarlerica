#include "../include/transactionStorage.h"
#include <chrono>
#include <string>
#include <fstream>
#include <thread>

int TransactionStorage::transactionCount = 0;

TransactionStorage::TransactionStorage()
{
    readTransactionsFromFile();
}

void TransactionStorage::addTransaction(float amount, std::string accountNumber)
{
    std::chrono::time_point t = std::chrono::system_clock::now();
    std::string date = std::to_string(std::chrono::system_clock::to_time_t(t));

    this->transactions.emplace_back(amount, date, std::to_string(transactionCount++), accountNumber);
}

void TransactionStorage::addTransaction(std::string unformattedString)
{
    std::vector<std::string> details;
    // [0] = ID
    // [1] = AccountNumber
    // [2] = Date
    // [3] = Sum

    int index = 0;

    for(int i = 0; i < unformattedString.length(); i++)
    {
        if(unformattedString[i] != ',')
        {
            details[index].push_back(unformattedString[i]);
            continue;
        }
        index++;
    }

    this->transactions.emplace_back(details[3], details[2], details[0], details[1]);
    transactionCount++;
}

std::vector<Transaction>& TransactionStorage::getTransactions()
{
    return this->transactions;
}

std::vector<Transaction*> TransactionStorage::getTransactions(std::string accountNumber)
{
    std::vector<Transaction*> temp;

    for(Transaction &transaction : this->transactions)
    {
        if(transaction.getAccountNumber() == accountNumber) temp.push_back(&transaction);
    }

    return temp;
}

Transaction* TransactionStorage::getTransaction(std::string transactionID)
{
    int s = 0;
    int e = this->transactions.size() - 1;

    while(s <= e)
    {
        int mid = (s + e) / 2;

        if(this->transactions[mid].getID() == transactionID) return &this->transactions[mid];
        else if(transactionID < this->transactions[mid].getID()) e = mid - 1;
        else s = mid + 1;
    }

    return nullptr;
}

void TransactionStorage::readTransactionsFromFile()
{   
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "READING FROM FILE" << std::endl;

    std::ifstream file(TRANSACTIONS_PATH);
    std::string temp;

    if(!file.is_open())
    {
        std::cout << "[readTransactionsFromFile] File was unable to open: " << TRANSACTIONS_PATH << std::endl;
        return;
    }

    while(std::getline(file, temp))
    {
        addTransaction(temp);
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "READING FROM FILE TOOK " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void TransactionStorage::writeTransactionsToFile()
{   
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "WRITING TO FILE" << std::endl;

    std::ofstream file(TRANSACTIONS_PATH);

    if(!file.is_open())
    {
        std::cout << "[writeTransactionsToFile] File was unable to open: " << TRANSACTIONS_PATH << std::endl;
        return;
    }

    for(Transaction &transaction : this->transactions)
    {
        file << transaction.getID() + "," + transaction.getAccountNumber() + "," + transaction.getDate() + "," + transaction.getAmount() << std::endl;
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "WRITING TO FILE TOOK " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}