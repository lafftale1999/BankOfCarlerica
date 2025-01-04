#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>

class Client
{
    std::string clientID;
    std::string firstName;
    std::string lastName;
    std::vector<std::string> accounts;

public:
    Client(std::string clientID);
    Client(std::string clientID, std::string firstName, std::string lastName, std::string accounts);
    Client(std::string clientID, std::string firstName, std::string lastName, std::vector<std::string> accounts);
    
    void removeClient();
    void setClientID(std::string clientID);
    void setFirstName(std::string firstName);
    void setLastName(std::string lastName);
    void addAccount(std::string account);
    
    std::string getClientId();
    std::string getFirstName();
    std::string getLastName();
    std::string getFullName();
    std::vector<std::string>& getAccounts();
    void removeAccount(std::string accountNumber);
};

#endif