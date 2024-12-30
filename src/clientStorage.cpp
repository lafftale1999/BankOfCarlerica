#include "../include/clientStorage.h"
#include <string>
#include <fstream>

ClientStorage::ClientStorage(int maxLimit)
{
    this->maxLimit = maxLimit;
}

ClientStorage::~ClientStorage()
{
    saveClientsToFile();
}

void ClientStorage::addClient(std::string firstName, std::string lastName, std::vector<std::string> accounts)
{
    if(clients.size() < maxLimit)
    {
        std::string id = std::string(std::to_string(this->maxLimit).length() - std::to_string(this->clients.size()).length(), '0') + std::to_string(clients.size());

        clients.emplace_back(id, firstName, lastName, accounts);
    }

    else
    {
        std::cout << "Clients list is full. Can't add more clients" << std::endl;
    }
}

Client* ClientStorage::findClient(std::string clientID)
{
    int s = 0;
    int e = this->clients.size() - 1;

    int c;

    while (s <= e)
    {
        c = (s + e) / 2;

        if(clientID == clients[c].getClientId()) return &clients[c];
        else if(clientID < clients[c].getClientId()) e = c - 1;
        else if(clientID > clients[c].getClientId()) s = c + 1;
    }

    return nullptr;
}

std::vector<Client>& ClientStorage::getClients()
{
    return this->clients;
}

void ClientStorage::loadClientsFromFile()
{
    std::ifstream file(CLIENT_PATH);

    if(!file.is_open())
    {
        std::cout << "Unable to open file: " << CLIENT_PATH << std::endl;
        return;
    }

    std::vector<std::string> temp;
    // 0 = id
    // 1 = firstName
    // 2 = lastName
    // 3 = accounts

    std::string tempString;
    int index;

    while(std::getline(file, tempString) && clients.size() < maxLimit)
    {
        for(auto t : temp) t = "";

        for(int i = 0; i < tempString.length(); i++)
        {
            if(tempString[i] == ',')
            {
                index++;
                continue;
            }

            temp[index].push_back(tempString[i]);
        }
        // 0 = id | 1 = fname | 2 = lname | 3 = accounts
        clients.emplace_back(temp[0], temp[1], temp[2], temp[3]);
        index = 0;
    }

    file.close();
}

void ClientStorage::saveClientsToFile()
{
    std::ofstream file(CLIENT_PATH);

    if(!file.is_open())
    {
        std::cout << "Unable to open file: " << CLIENT_PATH << std::endl;
        return;
    }

    for (auto c : clients)
    {
        if(c.getClientId().empty()) continue;

        file << c.getClientId() + ',' + c.getFirstName() + ',' + c.getLastName() + ',';

        for(int i = 0; i < c.getAccounts().size(); i++)
        {
            if(i == c.getAccounts().size() - 1) file << c.getAccounts()[i] + ',';
            else file << c.getAccounts()[i] + '|';
        }

        file << std::endl;
    }
}