#ifndef CLIENT_STORAGE_H
#define CLIENT_STORAGE_H

#include "client.h"

#define CLIENT_PATH "data/clients/clients.txt"

class ClientStorage
{
    std::vector<Client> clients;
    int maxLimit;

public:
    ClientStorage();
    ClientStorage(int maxLimit);
    ~ClientStorage();

    void addClient(std::string firstName, std::string lastName, std::vector<std::string> accounts);
    Client* findClient(std::string clientID);
    std::vector<Client>& getClients();

    void loadClientsFromFile();
    void saveClientsToFile();
<<<<<<< HEAD

=======
>>>>>>> d63df2e3900646a1437daec0bea7eec0d2f1d20c
    int getMaxLimit();
};

#endif