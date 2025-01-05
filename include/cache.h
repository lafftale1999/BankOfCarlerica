#ifndef __MY_CACHE_H
#define __MY_CACHE_H

#include <iostream>
#include <optional>
#include <vector>

// To use this Cache, the objects handled in cache must comply with cacheRequirements.h

template<typename T, size_t N>
class CacheLRU
{
    T cache[N];
    size_t size = 0;
    size_t max_size = N;

public:
    CacheLRU(){}
    
    std::optional<T> searchCache(const std::string string)
    {   
        for(size_t i = 0; i < size; i++)
        {
            if(string == cache[i].getID())
            {
                addToCache(cache[i]);
                return cache[0];
            }
        }
        return std::nullopt;
    }

    void addToCache(T item)
    {
        int foundAt = -1;

        for(size_t i = 0; i < size; i++)
        {
            if(cache[i].getID() == item.getID())
            {
                foundAt = i;
                break;
            }
        }

        if(foundAt != -1)
        {
            for(int i = foundAt; i > 0; i--)
            {
                cache[i] = cache[i-1];
            }
        }
        else
        {
            if(size < N) size++;

            for(size_t i = size - 1; i > 0; i--)
            {
                cache[i] = cache[i-1];
            }
        }

        cache[0] = item;
    }

    void printCache()
    {
        for(size_t i = 0; i < N; i++)
        {
            std::cout << cache[i] << std::endl;
        }
    }

    int getSize()
    {
        return this->size;
    }

    T* getCache()
    {
        return cache;
    }

    size_t getTemporaryArraySize()
    {
        return this->temporaryArraySize;
    }
};

#endif