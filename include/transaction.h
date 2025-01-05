#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include "cacheRequirements.h"

class Transaction : public CacheRequirements
{
    std::string accountNumber;
    std::string amount;
    std::string date;
    std::string ID;

public:
    Transaction();
    Transaction(std::string amount, std::string date, std::string ID, std::string accountNumber);
    void setAccountNumber(std::string accountNumber);
    void setAmount(std::string amount);
    void setDate(std::string date);
    void setID(std::string ID);

    std::string getAccountNumber();
    std::string getAmount();
    std::string getDate();
    std::string getID() const override final;
};

#endif