#include "../include/bankerUI.h"

#include <stdlib.h>
#include <string>
#include <algorithm>

MenuNavigation mainMenu()
{   
    std::map<int, std::pair<std::string, MenuNavigation>> menuOptions = 
    {
        {0,{"Serve next client", SERVE_NEXT_CLIENT}},
        {1,{"Help specific client", CHOOSE_CLIENT}},
        {2,{"Add new client", NEW_CLIENT}},
        {3,{"Find specific transaction", FIND_TRANSACTION}},
        {4,{"Find specific account", FIND_ACCOUNT}},
        {5,{"Exit", EXIT}}
    };

    printMenu(
        "MAIN MENU",
        "Choose what you want to do next",
        menuOptions
    );

    return getUserInput(menuOptions);
}

MenuNavigation serveClient(Bank* bank)
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

    std::string temp = std::string(bank->getClients()->getPadding() - std::to_string(userInput).length(), '0') + std::to_string(userInput);

    bank->setCurrentClient(temp);

    return SERVE_CLIENT;
}

MenuNavigation findTransaction(Bank* bank)
{
    printMenu("FIND SPECIFIC TRANSACTION", "Enter the transaction id:");

    int userInput;

    while(true)
    {
        std::cin >> userInput;

        // IF USER PUT IN NON NUMERIC SYMBOLS
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            continue;
        }

        if (userInput < 0 || userInput >= bank->getTransactionLink()->getTransactionLimit()) {
            std::cout << "Please enter a number between 0 and " << bank->getTransactionLink()->getTransactionLimit() - 1 << "." << std::endl;
            continue;
        }

        break;
    }

    std::string temp = std::string(bank->getTransactionLink()->getPadding() - std::to_string(userInput).length(), '0') + std::to_string(userInput);

    bank->setCurrentTransaction(bank->getTransactionLink()->getTransaction(temp));

    if(bank->getCurrentTransaction().getID().length() == 0)
    {
        std::cout << "The transaction does not exist!" << std::endl;
    }

    std::cout << bank->getCurrentTransaction().getID() + " | " << bank->getCurrentTransaction().getAccountNumber() + " | " + bank->getCurrentTransaction().getAmount() + "kr | " + bank->getCurrentTransaction().getDate() << std::endl;

    std::string waitingForInput;
    std::cin >> waitingForInput;

    return MAIN_MENU; 
}

MenuNavigation findSpecificAccount(Bank *bank)
{
    printMenu("FIND SPECIFIC ACCOUNT", "Enter the account number:");

    int userInput;

    while(true)
    {
        std::cin >> userInput;

        // IF USER PUT IN NON NUMERIC SYMBOLS
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            continue;
        }

        if (userInput < 0 || userInput >= bank->getAccounts()->getAccountLimit()) {
            std::cout << "Please enter a number between 0 and " << bank->getAccounts()->getAccountLimit() - 1 << "." << std::endl;
            continue;
        }

        break;
    }

    std::string temp = std::string(bank->getAccounts()->getPadding() - std::to_string(userInput).length(), '0') + std::to_string(userInput);

    bank->setCurrentAccount(temp);

    MenuNavigation nav = MAIN_MENU;

    if(bank->getCurrentAccount() != nullptr)
    {
        nav = showAccount(-1, bank);
    }
    else
    {
        std::cout << "Account " << temp << " does not exist" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return nav;
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

    if(lastName == "x" || lastName == "X") return MAIN_MENU;

    bank->getClients()->addClient(firstName, lastName, accounts);

    bank->setCurrentClient(bank->getClients()->getClients()[bank->getClients()->getClients().size() - 1].getClientId());

    return SERVE_CLIENT;
}

MenuNavigation createNewAccount(Bank *bank)
{
    printMenu(
        "OPEN NEW ACCOUNT",
        "Opening new account for " + bank->getCurrentClient()->getFullName()
    );

    bank->getCurrentClient()->addAccount(bank->getAccounts()->createNewAccount());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Account is opened!" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return SERVE_CLIENT;
}

MenuNavigation checkAccounts(Bank *bank)
{
    std::map<int, std::pair<std::string, MenuNavigation>> menuOptions;

    for(size_t i = 0; i <= bank->getCurrentClient()->getAccounts().size(); i++)
    {
        if(i == bank->getCurrentClient()->getAccounts().size())
        {
            menuOptions[i] = {"Back", SERVE_CLIENT};
            break;
        }

        menuOptions[i] = {bank->getCurrentClient()->getAccounts().at(i) + ' ' + std::to_string(bank->getAccounts()->findAccount(bank->getCurrentClient()->getAccounts().at(i))->getBalance()) + " kr", ACCOUNT_CHOOSEN};
    }

    printMenu(
        "CHECK ACCOUNTS",
        "You are now serving " + bank->getCurrentClient()->getFullName() + " with " + std::to_string(bank->getCurrentClient()->getAccounts().size()) + " accounts.",
        menuOptions
    );

    int userInput = getUserInputInt(menuOptions);
    MenuNavigation nav;

    if((size_t)userInput < bank->getCurrentClient()->getAccounts().size())
    {
        nav = showAccount(userInput, bank);
    }
    
    return nav;
}

MenuNavigation showAccount(int index, Bank *bank)
{
    std::map<int, std::pair<std::string, MenuNavigation>> menuOptions =
    {
        {0,{"Show transactions", SHOW_TRANSACTIONS}},
        {1,{"Update balance", UPDATE_BALANCE}},
        {2,{"Close Account", CLOSE_ACCOUNT}},
        {3,{"Back", CHECK_ACCOUNT}}
    };
    
    if(index != -1) bank->setCurrentAccount(bank->getCurrentClient()->getAccounts()[index]);

    while(true)
    {
        printMenu(
            "CHECK YOUR ACCOUNT",
            "Current account is " + bank->getCurrentAccount()->getAccountNumber() + " with a balance of " + std::to_string(bank->getCurrentAccount()->getBalance()) + "kr",
            menuOptions
        );

        MenuNavigation nav = getUserInput(menuOptions);

        switch(nav)
        {
            case SHOW_TRANSACTIONS:
                showTransactions(bank->getCurrentAccount());
                continue;

            case UPDATE_BALANCE:
                updateBalance(bank->getCurrentAccount());
                continue;
            
            case CLOSE_ACCOUNT:
                bank->getCurrentClient()->removeAccount(bank->getCurrentAccount()->getAccountNumber());
                bank->getCurrentAccount()->~Account();

                std::cout << "Account closed!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return SERVE_CLIENT;

            case CHECK_ACCOUNT:
                if(index == -1) return MAIN_MENU;
                return SERVE_CLIENT;

            default:
                std::cout << "Something went wrong, please try again!" << std::endl;
        }
    }    
}

void showTransactions(Account* account)
{
    printMenu(
        "SHOW TRANSACTIONS",
        "Account: " + account->getAccountNumber() + " with a balance of " + std::to_string(account->getBalance()) + "kr. Enter (x) to go back!"
    );

    for(auto t : account->getTransactionHistory())
    {
        std::cout << t.getID() + " | " + t.getAccountNumber() + " | " + t.getAmount() + "kr | " + t.getDate() << std::endl;
    }

    std::string waitForInput;
    std::cin >> waitForInput;
}

void updateBalance(Account* account)
{
    printMenu(
        "UPDATE BALANCE",
        "Account: " + account->getAccountNumber() + " with a balance of " + std::to_string(account->getBalance()) + "kr.\nEnter the amount to update or 0 and enter to go back"
    );

    float userInput = 0;

    while(true)
    {
        try
        {
            std::cin >> userInput;
            break;
        }

        catch(const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    if(userInput != 0)
    {
        SuccessMessage balanceUpdated = account->updateBalance(userInput);

        if(balanceUpdated == SUCCESS) std::cout << "Account balance has been updated" << std::endl;
        else if(balanceUpdated == FAILED) std::cout << "Failed to update account balance" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// WITH MENU OPTIONS
void printMenu(std::string headline, std::string message, std::map<int, std::pair<std::string, MenuNavigation>> menuOptions)
{
    system("cls");

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
        std::for_each(std::begin(menuOptions), std::end(menuOptions),[](auto const &option){
            std::cout << option.first << ". " << option.second.first << std::endl;
        });

        /* for(auto i = menuOptions.begin(); i != menuOptions.end(); i++)
        {
            std::cout << i->first << ". " << i->second.first << std::endl;
        } */
    }
}

// WITHOUT MENU OPTIONS
void printMenu(std::string headline, std::string message)
{
    system("cls");
    
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
        std::cin >> userChoice;

        // IF USER PUT IN NON NUMERIC SYMBOLS
        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            continue;
        }

        if (userChoice < 0 || (size_t)userChoice >= menuOptions.size()) {
            std::cout << "Please enter a number between 0 and " << menuOptions.size() - 1 << "." << std::endl;
            continue;
        }

        return menuOptions[userChoice].second;
    }
}

int getUserInputInt(std::map<int, std::pair<std::string, MenuNavigation>> menuOptions)
{
    int userChoice;

    while(true)
    {
        std::cin >> userChoice;

        // IF USER PUT IN NON NUMERIC SYMBOLS
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            continue;
        }

        if (userChoice < 0 || (size_t)userChoice >= menuOptions.size()) {
            std::cout << "Please enter a number between 0 and " << menuOptions.size() - 1 << "." << std::endl;
            continue;
        }

        return userChoice;
    }
}