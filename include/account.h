#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transactionLink.h"

typedef enum
{
    BALANCE_UPDATED,
    BALANCE_TOO_LOW
} SuccessMessage;

class Account
{
    std::string accountNumber;
    float balance;
    std::vector<Transaction> transactionHistory;

public:
    Account();
    Account(std::string accountNumber);
    Account(std::string accountNumber, std::string balance);
    ~Account();
    void setAccountNumber(std::string accountNumber);
    SuccessMessage updateBalance(float amount);

    std::string getAccountNumber();
    float getBalance();

    std::vector<Transaction> getTransactionHistory();

    void closeAccount();
};

#endif