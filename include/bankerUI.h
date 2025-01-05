#ifndef __BANKER_UI_H
#define __BANKER_UI_H

#include <iostream>
#include "bank.h"
typedef enum
{
    MAIN_MENU,
    SERVE_CLIENT,
    SERVE_NEXT_CLIENT,
    CHOOSE_CLIENT,
    NEW_CLIENT,
    FIND_TRANSACTION,
    FIND_ACCOUNT,
    CHECK_ACCOUNT,
    CREATE_ACCOUNT,
    CLOSE_ACCOUNT,
    ACCOUNT_CHOOSEN,
    SHOW_TRANSACTIONS,
    UPDATE_BALANCE,
    EXIT
}MenuNavigation;

MenuNavigation mainMenu();
MenuNavigation serveClient(Bank* bank);
MenuNavigation chooseClient(Bank *bank);
MenuNavigation newClient(Bank *bank);
MenuNavigation createNewAccount(Bank *bank);
MenuNavigation checkAccounts(Bank *bank);
MenuNavigation findSpecificAccount(Bank *bank);
MenuNavigation showAccount(int index, Bank *bank);
MenuNavigation findTransaction(Bank* bank);


void showTransactions(Account* account);
void updateBalance(Account* account);

// WITH MENU OPTIONS
void printMenu(std::string headline, std::string message, std::map<int, std::pair<std::string, MenuNavigation>> menuOptions);

// WITHOUT MENU OPTIONS
void printMenu(std::string headline, std::string message);
MenuNavigation getUserInput(std::map<int, std::pair<std::string, MenuNavigation>> menuOptions);
int getUserInputInt(std::map<int, std::pair<std::string, MenuNavigation>> menuOptions);

#endif