#include "../include/clientStorage.h"
#include <string>
#include <fstream>
#include <chrono>
#include <cmath>
#include <thread>

ClientStorage::ClientStorage(){};

ClientStorage::ClientStorage(int maxLimit)
{
    this->maxLimit = maxLimit;
    loadClientsFromFile();
    if(clients.size() > 0)
    {
        padding = clients[0].getClientId().length();
    }

    else
    {
        padding = std::to_string(maxLimit).length();
    }
}

ClientStorage::~ClientStorage()
{
    saveClientsToFile();
}

void ClientStorage::addClient(std::string firstName, std::string lastName, std::vector<std::string> accounts)
{
    if(clients.size() < (size_t)maxLimit)
    {
        std::string id = std::string(padding - std::to_string(clients.size()).length(), '0') + std::to_string(clients.size());

        clients.emplace_back(id, firstName, lastName, accounts);
    }

    else
    {
        std::cout << "Clients list is full. Can't add more clients" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

Client* ClientStorage::findClient(std::string clientID)
{
    std::cout << "Looking for client" << std::endl;
    auto begin = std::chrono::high_resolution_clock::now();

    int s = 0;
    int e = this->clients.size() - 1;

    int c;

    while (s <= e)
    {
        c = (s + e) / 2;

        if(clientID == clients[c].getClientId())
        {
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Finding client took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            return &clients[c];
        }

        else if(clientID < clients[c].getClientId()) e = c - 1;
        else if(clientID > clients[c].getClientId()) s = c + 1;
    }

    std::cout << "Could not find client id " << clientID << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return nullptr;
}

std::vector<Client>& ClientStorage::getClients()
{
    return this->clients;
}

void ClientStorage::loadClientsFromFile()
{
    std::ifstream file(CLIENT_PATH);

    std::cout << "READING CLIENTS FROM FILE" << std::endl;
    auto begin = std::chrono::high_resolution_clock::now();

    if(!file.is_open())
    {
        std::cout << "Unable to open file: " << CLIENT_PATH << std::endl;
        return;
    }

    std::string tempString;
    int index = 0;

    while(std::getline(file, tempString))
    {
        std::vector<std::string> temp(4);
        // 0 = id
        // 1 = firstName
        // 2 = lastName
        // 3 = accounts

        for(size_t i = 0; i < tempString.length(); i++)
        {
            if(tempString[i] == ',')
            {
                index++;
                continue;
            }

            temp[index].push_back(tempString[i]);
        }

        std::string accounts = temp[3];
        
        // 0 = id | 1 = fname | 2 = lname | 3 = accounts
        clients.emplace_back(temp[0], temp[1], temp[2], temp[3]);
        index = 0;
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "READING CLIENTS TOOK: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
}

void ClientStorage::saveClientsToFile()
{
    std::ofstream file(CLIENT_PATH);

    std::cout << "WRITING CLIENTS TO FILE" << std::endl;
    auto begin = std::chrono::high_resolution_clock::now();

    if(!file.is_open())
    {
        std::cout << "Unable to open file: " << CLIENT_PATH << std::endl;
        return;
    }

    for (auto c : clients)
    {
        if(c.getClientId().empty()) continue;

        file << c.getClientId() + ',' + c.getFirstName() + ',' + c.getLastName() + ',';

        for(size_t i = 0; i < c.getAccounts().size(); i++)
        {
            if(i == c.getAccounts().size() - 1) file << c.getAccounts()[i] + ',';
            else file << c.getAccounts()[i] + '|';
        }

        file << std::endl;
    }

    file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "SAVING CLIENTS TOOK: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
}

int ClientStorage::getMaxLimit()
{
    return this->maxLimit;
}

int ClientStorage::getPadding()
{
    return this->padding;
}