#include "../include/transactionLink.h"
#include <chrono>
#include <string>
#include <fstream>
#include <thread>
#include <iomanip>
#include <sstream>
#include <ctime>

int TransactionLink::transactionLimit = 0;
int TransactionLink::transactionCount = 0;
int TransactionLink::padding = 0;

TransactionLink::TransactionLink(){}

TransactionLink::TransactionLink(int transactionLimit)
{
    TransactionLink::transactionLimit = transactionLimit;
    init();

    if(!padding) padding = std::to_string(transactionLimit).length();
}

TransactionLink::TransactionLink(std::string accountNumber)
{
    for(Transaction t : this->getTransactions(accountNumber))
    {
        this->currentTransactions.push_back(t);
    }
}

std::vector<Transaction> TransactionLink::getCurrentTransactions()
{
    return this->currentTransactions;
}

void TransactionLink::init()
{
    readTransactionsFromFile();
}

void TransactionLink::addTransaction(std::string amount, std::string accountNumber)
{
    std::time_t now = std::time(nullptr);
    std::tm localTime = *std::localtime(&now);

    std::ostringstream dateTimeStream;
    dateTimeStream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    std::string ID = std::string(padding - std::to_string(TransactionLink::transactionCount).length(), '0') + std::to_string(TransactionLink::transactionCount);
     
    Transaction transaction(amount, dateTimeStream.str(), ID, accountNumber);
    writeTransactionToFile(transaction);

    TransactionLink::transactionCount++;
}

Transaction TransactionLink::formatTransaction(std::string unformattedString)
{
    std::vector<std::string> details(4);
    // [0] = ID
    // [1] = AccountNumber
    // [2] = Date
    // [3] = Sum

    int index = 0;

    for(size_t i = 0; i < unformattedString.length(); i++)
    {
        if(unformattedString[i] != ',')
        {
            details[index].push_back(unformattedString[i]);
            continue;
        }
        index++;
    }

    Transaction transaction(details.at(3), details[2], details[0], details[1]);
    
    return transaction;
}

Transaction TransactionLink::getTransaction(std::string transactionID)
{   
    Transaction* transaction = transactionCache.searchCache(transactionID);

    if(transaction) return *transaction;

    std::string temp;
    bool isFound = false;

    std::ifstream file(TRANSACTIONS_PATH);

    if(!file.is_open())
    {
        std::cout << "File does not exist: " << TRANSACTIONS_PATH << std::endl;
        throw;
    }

    while(std::getline(file, temp))
    {
        if(temp.find(transactionID) != std::string::npos) 
        {
            isFound = true;
            break;
        }
    }

    if(isFound)
    {
        Transaction t = formatTransaction(temp);
        transactionCache.addToCache(t);
        return t;
    }

    return Transaction();
}

std::vector<Transaction> TransactionLink::getTransactions(std::string accountNumber)
{
    std::vector<Transaction> transactionList;

    std::string tempString;
    std::ifstream file(TRANSACTIONS_PATH);

    while (std::getline(file, tempString)) {
        // Dela upp raden i fält baserat på komma
        std::stringstream ss(tempString);
        std::string field;
        std::vector<std::string> fields;

        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Kontrollera om första fältet exakt matchar accountNumber
        if (!fields.empty() && fields[1] == accountNumber) {
            Transaction t(formatTransaction(tempString));
            transactionList.push_back(t);
            transactionCache.addToCache(t);
        }
    }

    file.close();

    return transactionList;
}

void TransactionLink::readTransactionsFromFile()
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
        TransactionLink::transactionCount++;
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "READING FROM FILE TOOK " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void TransactionLink::writeTransactionToFile(Transaction& transaction)
{   
    std::ofstream file(TRANSACTIONS_PATH, std::ios::app);

    if(!file.is_open())
    {
        std::cout << "[writeTransactionsToFile] File was unable to open: " << TRANSACTIONS_PATH << std::endl;
        return;
    }

    file << transaction.getID() + ',' + transaction.getAccountNumber() + ',' + transaction.getDate() + ',' + transaction.getAmount() + ',' << std::endl;
    
    file.close();
}

void TransactionLink::readFirstLine()
{
    std::ifstream file(TRANSACTIONS_PATH);
    std::string temp;

    std::string tempId;

    if(!file.is_open())
    {
        std::cout << "Unable to open file [readFirstLine()]: " << TRANSACTIONS_PATH << std::endl;
        return;
    }

    while(std::getline(file,temp))
    {
        for(size_t i = 0; i < temp.size(); i++)
        {
            if(temp[i] == ',') break;
            tempId.push_back(temp[i]);
        }

        break;
    }

    TransactionLink::padding = tempId.length();
}