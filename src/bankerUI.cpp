#include "../include/bankerUI.h"
#include "../include/bank.h"

#include <stdlib.h>
#include <string>

int navigation(Bank* bank)
{
    MenuNavigation layer = MAIN_MENU;

    while(true)
    {   
        switch(layer)
        {
            case MAIN_MENU:
                layer = mainMenu();
                continue;

            case NEXT_CLIENT:
                bank->setNextClient();
                layer = nextClient(bank);
                continue;

            case CHOOSE_CLIENT:
                layer = chooseClient(bank);
                continue;

            case NEW_CLIENT:
                layer = newClient(bank);
                continue;

            case CHECK_ACCOUNT:
                continue;
        }
    }
}

MenuNavigation mainMenu()
{   
    std::map<int, std::pair<std::string, MenuNavigation>> menuOptions = 
    {
        {0,{"Serve next client", NEXT_CLIENT}},
        {1,{"Help specific client", CHOOSE_CLIENT}},
        {2,{"Add new client", NEW_CLIENT}},
        {3,{"Exit", EXIT}}
    };

    system("cls");

    printMenu(
        "MAIN MENU",
        "Choose what you want to do next",
        menuOptions
    );

    return getUserInput(menuOptions);
}

MenuNavigation nextClient(Bank* bank)
{
    if(bank->getCurrentClient())
    {
        std::map<int, std::pair<std::string, MenuNavigation>> menuOptions = 
        {
            {0,{"Check accounts", CHECK_ACCOUNT}},
            {1,{"Open new account", CREATE_ACCOUNT}},
            {2,{"Finish", MAIN_MENU}}
        };

        printMenu(
        "SERVE NEXT CLIENT",
        "You are now serving " + bank->getCurrentClient()->getFullName() + " with " + std::to_string(bank->getCurrentClient()->getAccounts().size()) + " accounts.",
        menuOptions);
        
        return getUserInput(menuOptions);
    }

    else
    {
        std::cout << "No client found. Going back to main menu" << std::endl;
        return MAIN_MENU;
    }
}

MenuNavigation chooseClient(Bank *bank)
{   
    printMenu("CHOOSE NEXT CLIENT", "Enter the clients id:");

    int userInput;

    while (true)
    {
        try
        {
            std::cin >> userInput;

            if(userInput < 0 || userInput > bank->getClients()->getMaxLimit())
            {
                std::cout << "Please enter a valid number" << std::endl;
                continue;
            }

            break;
        }

        catch(const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    std::string temp = std::string(std::to_string(userInput).length() - bank->getClients()->getMaxLimit(), '0') + std::to_string(userInput);

    bank->setCurrentClient(temp);

    return NEXT_CLIENT;
}

MenuNavigation newClient(Bank *bank)
{
    printMenu("NEW CLIENT", "Creating new client - enter 'x' to go back!");
    std::cout << "Enter the clients first name: ";
    
    std::string firstName;
    std::string lastName;
    std::vector<std::string> accounts;

    while(true)
    {
        std::cin >> firstName;

        if(firstName.length() == 0)
        {
            std::cout << "Enter the clients complete first name" << std::endl;
            continue;
        }

        break;
    }

    if(firstName == "x" || firstName == "X") return MAIN_MENU;

    std::cout << "Enter the clients last name: ";
    while(true)
    {
        std::cin >> lastName;

        if(lastName.length() == 0)
        {
            std::cout << "Enter the clients complete last name" << std::endl;
            continue;
        }

        break;
    }

    bank->getClients()->addClient(firstName, lastName, accounts);

    bank->setCurrentClient(bank->getClients()->getClients()[bank->getClients()->getClients().size() - 1].getClientId());

    return NEXT_CLIENT;
}



// WITH MENU OPTIONS
void printMenu(std::string headline, std::string message, std::map<int, std::pair<std::string, MenuNavigation>> menuOptions)
{
    if(!headline.empty())
    {
        std::cout << headline << std::endl;
    }

    if(!headline.empty())
    {
        std::cout << message << std::endl;
    }

    std::cout << "-----------------------------------" << std::endl;

    if(!menuOptions.empty())
    {
        for(auto i = menuOptions.begin(); i != menuOptions.end(); i++)
        {
            std::cout << i->first << std::endl;
        }
    }
}

// WITHOUT MENU OPTIONS
void printMenu(std::string headline, std::string message)
{
    if(!headline.empty())
    {
        std::cout << headline << std::endl;
    }

    if(!headline.empty())
    {
        std::cout << message << std::endl;
    }

    std::cout << "-----------------------------------" << std::endl;
}

MenuNavigation getUserInput(std::map<int, std::pair<std::string, MenuNavigation>> menuOptions)
{
    int userChoice;

    while(true)
    {
        try
        {
            std::cin >> userChoice;
            
            if(userChoice >= menuOptions.size() || userChoice < 0)
            {
                std::cout << "Please enter a number between " << 0 << " and " << menuOptions.size() - 1 << std::endl;
                continue; 
            }

            return menuOptions[userChoice].second;
        }

        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}