#include "../include/transaction.h"
#include <string>

Transaction::Transaction()
{
    setAmount("N/F");
    setDate("N/F");
    setAccountNumber("N/F");
    setID("N/F");
}
Transaction::Transaction(std::string amount, std::string date, std::string ID, std::string accountNumber)
{
    setAmount(amount);
    setDate(date);
    setAccountNumber(accountNumber);
    setID(ID);
}

void Transaction::setAccountNumber(std::string accountNumber)
{
    this->accountNumber = accountNumber;
}

void Transaction::setAmount(std::string amount)
{
    this->amount = amount;
}

void Transaction::setDate(std::string date)
{
    this->date = date;
}

void Transaction::setID(std::string ID)
{
    this->ID = ID;
}

std::string Transaction::getAccountNumber()
{
    return this->accountNumber;
}

std::string Transaction::getAmount()
{
    return this->amount;
}

std::string Transaction::getDate()
{
    return this->date;
}

std::string Transaction::getID()
{
    return this->ID;
}