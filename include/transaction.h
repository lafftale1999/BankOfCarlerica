#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>

class Transaction
{
    std::string accountNumber;
    std::string amount;
    std::string date;
    std::string ID;

public:
    Transaction(float amount, std::string date, std::string ID, std::string accountNumber);
    void setAccountNumber(std::string accountNumber);
    void setAmount(float amount);
    void setDate(std::string date);
    void setID(std::string ID);

    std::string getAccountNumber();
    std::string getAmount();
    std::string getDate();
    std::string getID();
};

#endif