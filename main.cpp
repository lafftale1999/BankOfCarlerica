#include "include/accountStorage.h"

int main(void)
{
    srand(time(NULL));

    int amount = 100;

    AccountStorage as(amount);
    TransactionLink ts(amount);

    for(auto t : as.getMap()["099"].getTransactionHistory())
    {
        std::cout << t.getAmount() << " was transferred " << t.getDate() << " by account " << t.getAccountNumber() << std::endl;
    }

    return 0;
}