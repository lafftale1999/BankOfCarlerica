#include "../include/generateClients.h"
#include <fstream>
#include <string>
#include <iostream>

GenerateClients::GenerateClients(int amount)
{
    bank = Bank(amount);
    // cleanFiles();

    loadNames(FIRSTNAME);
    loadNames(LASTNAME);

    for(int i = 0; i < amount; i++)
    {
        int fname = rand() % firstNames.size();
        int lname = rand() % lastNames.size();
        int n_of_accounts = (rand() % 3) + 1;

        std::vector<std::string> listOfAccounts;

        for(int i = 0; i < n_of_accounts; i++)
        {
            listOfAccounts.push_back(this->bank.getAccounts()->createNewAccount());
        }

        bank.getClients()->addClient(firstNames[fname], lastNames[lname], listOfAccounts);
    }
}

void GenerateClients::loadNames(std::string path)
{
    std::ifstream file(path);

    if(!file.is_open())
    {
        std::cout << "unable to open file: " << path << std::endl;
        return;
    }

    std::string temp;

    while(std::getline(file, temp))
    {
        if(path == FIRSTNAME) firstNames.push_back(temp);
        else lastNames.push_back(temp);
    }

    file.close();
}

void GenerateClients::cleanFiles()
{
    std::ofstream cfile(CLIENT_PATH);
    if(cfile.is_open()) cfile << "";
    cfile.close();

    std::ofstream afile(ACCOUNTS_PATH);
    if(afile.is_open()) afile << "";
    afile.close();
}