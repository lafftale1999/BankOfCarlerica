#include "../include/account.h"
#include <gtest/gtest.h>

#include <string>

class AccountTest : public testing::Test
{
protected:
    void SetUp() override
    {
        //game_initialized();
    }
};

TEST_F(AccountTest, whenBalanceIsTooLow)
{
    // ARRANGE - "setup"
    Account account("testBalanceIsTooLow", "5000");
    TransactionLink tl(100000000);

    // ACT - "do the test"
    SuccessMessage message = account.updateBalance((-6000));

    // ASSERT - "verify the testresult"
    ASSERT_EQ(message, BALANCE_TOO_LOW);
}

TEST_F(AccountTest, whenUpdateBalanceSucceed)
{
    Account account("testBalanceSucceed", "5000");
    TransactionLink tl(100000000);

    SuccessMessage message = account.updateBalance(3000);

    ASSERT_EQ(message, BALANCE_UPDATED);
    ASSERT_EQ(8000.0f, account.getBalance());
}

