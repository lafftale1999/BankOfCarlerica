#include "include/threadPool.h"
#include "include/bankerUI.h"
#include "include/generateClients.h"

#include <random>

int main(void)
{
    // Maximum limit of all storage used in the bank
    int bankSize = 1000000;

    // uncomment this if you want to generate new clients
    // GenerateClients generateClients(bankSize);

    // LOADING FILES
    ClientStorage cs(bankSize * 10);
    AccountStorage as(bankSize * 100);
    TransactionLink tl (bankSize * 10000);

    // CREATING THE BANK
    Bank bank(&as, &cs, &tl);

    // CREATING THE THREAD POOL BASED ON AVAILABLE THREADS
    ThreadPool threadPool(std::thread::hardware_concurrency());

    // LOGIC FOR FILLING THE QUEUE
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, bank.getClients()->getClients().size());

    threadPool.enqueue([&bank, &gen, &dis]{
        while(bank.getQueue().isRunning())
        {
            int rnd = dis(gen);
            std::string id = std::string(bank.getClients()->getPadding() - std::to_string(rnd).length(), '0') + std::to_string(rnd);
            bank.getQueue().enqueue(id);
        }
    });

    // LOGIC FOR NAVIGATION THE PROGRAM
    MenuNavigation layer = MAIN_MENU;

    while(true)
    {   
        switch(layer)
        {
            case MAIN_MENU:
                layer = mainMenu();
                continue;

            case SERVE_NEXT_CLIENT:
                bank.setNextClient();
                layer = serveClient(&bank);
                continue;

            case SERVE_CLIENT:
                layer = serveClient(&bank);
                continue;

            case CHOOSE_CLIENT:
                layer = chooseClient(&bank);
                continue;

            case NEW_CLIENT:
                layer = newClient(&bank);
                continue;

            case CHECK_ACCOUNT:
                layer = checkAccount(&bank);
                continue;

            case CREATE_ACCOUNT:
                layer = createNewAccount(&bank);
                continue;

            case EXIT:
                bank.getQueue().stopQueue();
                break;

            default:
                std::cout << "Something went wrong, going back to main menu" << std::endl;
                layer = MAIN_MENU;
                continue;
        }
        break;
    }

    return 0;
}
