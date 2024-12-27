#include "../include/transaction.h"
#include <string>

Transaction::Transaction(float amount, std::string date)
{
    setAmount(amount);
    setDate(date);
}

void Transaction::setAmount(float amount)
{
    this->amount = std::to_string(amount);
}

void Transaction::setDate(std::string date)
{
    this->date = date;
}

std::string Transaction::getAmount()
{
    return this->amount;
}

std::string Transaction::getDate()
{
    return this->date;
}