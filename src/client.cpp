#include "../include/client.h"

Client::Client(std::string clientID)
{

}

Client::Client(std::string clientID, std::string firstName, std::string lastName, std::vector<std::string> accounts)
{
    setClientID(clientID);
    setFirstName(firstName);
    setLastName(lastName);
    
    for(auto a : accounts) addAccount(a);
}

void Client::removeClient()
{
    setFirstName("Closed");
    setLastName("Closed");
    this->accounts = std::vector<std::string>();
}

void Client::setClientID(std::string clientID)
{
    this->clientID = clientID;
}

void Client::setFirstName(std::string firstName)
{
    this->firstName = firstName;
}

void Client::setLastName(std::string lastName)
{
    this->lastName = lastName;
}

void Client::addAccount(std::string account)
{
    this->accounts.push_back(account);
}

std::string Client::getClientId()
{
    return this->clientID;
}

std::string Client::getFirstName()
{
    return this->firstName;
}

std::string Client::getLastName()
{
    return this->lastName;
}

std::vector<std::string>& Client::getAccounts()
{
    return this->accounts;
}