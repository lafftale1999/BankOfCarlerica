#include "include/generateClients.h"
#include "include/threadPool.h"

int main(void)
{

    GenerateClients gen(10);

    /* Bank bank(1000);

    MenuNavigation layer = MAIN_MENU;

    while(true)
    {   
        switch(layer)
        {
            case MAIN_MENU:
                layer = mainMenu();
                continue;

            case SERVE_CLIENT:
                bank.setNextClient();
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
                break;
        }

        break;
    }
 */
    return 0;

}
