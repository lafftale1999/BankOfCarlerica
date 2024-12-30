#include "include/accountStorage.h"
#include "include/client.h"
#include "include/cache.h"

int main(void)
{
    // needed for seeding rng
    srand(time(NULL));

    TransactionLink ts(100);
    Transaction t = ts.getTransaction("001");

    std::cout << t.getID() + " " + t.getAccountNumber() + " " + t.getDate() << std::endl;

    return 0;
}