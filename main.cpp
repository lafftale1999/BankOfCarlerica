#include "include/threadPool.h"
#include "include/bankerUI.h"
#include <random>

int main(void)
{
    int bankSize = 10000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, bankSize);

    Bank bank(bankSize);
    ThreadPool threadPool(std::thread::hardware_concurrency());
    MenuNavigation layer = MAIN_MENU;

    threadPool.enqueue([&bank, &gen, &dis]{
        while(bank.getQueue().isRunning())
        {
            int rnd = dis(gen);
            std::string id = std::string(std::to_string(bank.getClients()->getClients().size()).length() - std::to_string(rnd).length() + 1, '0') + std::to_string(rnd);
            bank.getQueue().enqueue(id);
        }
    });

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
