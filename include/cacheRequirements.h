#ifndef CACHE_REQUIREMENTS_H
#define CACHE_REQUIREMENTS_H

#include <iostream>

class CacheRequirements
{
    virtual std::string getID() const = 0;
    virtual std::string getAccountNumber() const = 0;
};

#endif