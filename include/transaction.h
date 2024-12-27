#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>

class Transaction
{
    std::string amount;
    std::string date;

public:
    Transaction(float amount, std::string date);
    void setAmount(float amount);
    void setDate(std::string date);
    std::string getAmount();
    std::string getDate();
};

#endif