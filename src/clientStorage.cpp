#include "../include/clientStorage.h"
#include <sstream>
#include <iostream>
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

    int start = 0;
    int end = this->clients.size() - 1;

    int mid;

    while (start <= end)
    {
        mid = (start + end) / 2;

        if(clientID == clients[mid].getClientId())
        {
            auto finish = std::chrono::high_resolution_clock::now();
            std::cout << "Finding client took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - begin).count() << " nanoseconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            return &clients[mid];
        }

        else if(clientID < clients[mid].getClientId()) end = mid - 1;
        else if(clientID > clients[mid].getClientId()) start = mid + 1;
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

    while(std::getline(file, tempString))
    {
        int index = 0;
        std::string token;

        std::vector<std::string> temp(CLIENT_TOKENS);
        // 0 = id
        // 1 = firstName
        // 2 = lastName
        // 3 = accounts

        std::stringstream stringStream(tempString);

        while(std::getline(stringStream, token, ','))
        {
            if(index < CLIENT_TOKENS) temp[index++] = token;
            else break;
        }
        
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