#ifndef GENERATE_CLIENTS_H
#define GENERATE_CLIENTS_H

#include "bank.h"

#define FIRSTNAME "data/names/firstNames.txt"
#define LASTNAME "data/names/lastNames.txt"

class GenerateClients
{
    Bank *bank;

    std::vector<std::string> firstNames;
    std::vector<std::string> lastNames;

public:
    GenerateClients(int amount);
    void loadNames(std::string path);
    void cleanFiles();
};

#endif