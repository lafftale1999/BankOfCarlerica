#include "../include/account.h"
#include <string>

Account::Account(){}

Account::Account(std::string accountNumber)
{
    setAccountNumber(accountNumber);
    
    // CREATING SOME RANDOM SUMS TO SIMULATE BALANCE ON ACCOUNTS
    balance = 0;
    int rnd = (rand() % 100) * 1000;
    updateBalance(rnd);
}

Account::Account(std::string accountNumber, std::string balance)
{
    setAccountNumber(accountNumber);
    this->balance = std::stof(balance);
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
    if((this->balance + amount) < 0)
    {
        std::cout << "Unable to withdraw " << amount << "kr from this account with " << this->balance << "kr!" << std::endl;
        return BALANCE_TOO_LOW;
    }

    this->balance += amount;
    TransactionLink transactionLink;
    transactionLink.addTransaction(std::to_string(amount), this->accountNumber);

    return BALANCE_UPDATED;
}

std::string Account::getAccountNumber()
{
    return this->accountNumber;
}

float Account::getBalance()
{
    return this->balance;
}

std::vector<Transaction> Account::getTransactionHistory()
{
    TransactionLink tsLink(this->accountNumber);
    
    this->transactionHistory = tsLink.getCurrentTransactions();

    return this->transactionHistory;
}

void Account::closeAccount()
{
    this->~Account();
}