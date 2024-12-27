#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transactionStorage.h"

typedef enum
{
    SUCCESS,
    FAILED
} SuccessMessage;

class Account
{
    std::string accountNumber;
    float balance;

public:
    Account(std::string accountNumber);
    ~Account();
    void setAccountNumber(std::string accountNumber);
    SuccessMessage updateBalance(float amount);

    std::string getAccountNumber();
    float getBalance();

    void closeAccount();
};

#endif