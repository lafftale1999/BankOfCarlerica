#include "../include/account.h"

Account::Account(std::string accountNumber)
{
    srand(time(NULL));

    int rnd = (rand() % 100) * 1000;

    this->balance = (float)rnd;
    setAccountNumber(accountNumber);
}

Account::~Account()
{
    accountNumber = "CLOSED";
    balance = 0;
}

void Account::setAccountNumber(std::string accountNumber)
{
    this->accountNumber = accountNumber;
}

SuccessMessage Account::updateBalance(float amount)
{
    if((this->balance - amount) < 0)
    {
        std::cout << "Unable to withdraw " << amount << "kr from this account with " << this->balance << "kr!" << std::endl;
        return FAILED;
    }


    this->balance -= amount;
    return SUCCESS;
}

std::string Account::getAccountNumber()
{
    return this->accountNumber;
}

float Account::getBalance()
{
    return this->balance;
}

void Account::closeAccount()
{
    this->~Account();
}