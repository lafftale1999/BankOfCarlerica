#ifndef CLIENT_STORAGE_H
#define CLIENT_STORAGE_H

#include "client.h"

#define CLIENT_PATH "data/clients/clients.txt"

class ClientStorage
{
    std::vector<Client> clients;
    int maxLimit;
    int padding;

public:
    ClientStorage();
    ClientStorage(int maxLimit);
    ~ClientStorage();

    void addClient(std::string firstName, std::string lastName, std::vector<std::string> accounts);
    Client* findClient(std::string clientID);
    std::vector<Client>& getClients();

    void loadClientsFromFile();
    void saveClientsToFile();
    int getMaxLimit();
    int getPadding();
};

#endif