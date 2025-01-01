#include "include/generateClients.h"

int main(void)
{
    // needed for seeding rng
    srand(time(NULL));

    {
        GenerateClients gen(10);
    }

    std::cout << "here" << std::endl;
    /* Bank bank(100);

    int ci = 26;
    std::string firstName = bank.getClients()->getClients()[ci].getFirstName();
    std::string lastName = bank.getClients()->getClients()[ci].getLastName();
    // std::string account = bank.getClients()->getClients()[ci].getAccounts()[1];

    std::cout << firstName << ' ' << lastName << ' ' << std::endl;

    for(auto account : bank.getClients()->getClients()[ci].getAccounts())
    {
        std::cout << bank.getAccounts()->findAccount(account).getAccountNumber() << ": ";
        std::cout << bank.getAccounts()->findAccount(account).getBalance() << "kr " <<std::endl;
    } */
    
    
    return 0;
}