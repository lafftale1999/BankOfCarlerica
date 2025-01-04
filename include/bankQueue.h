#ifndef BANK_QUEUE_H
#define BANK_QUEUE_H

#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <optional>
#include <iostream>
#include <chrono>

template<typename T, size_t N>
class BankQueue
{
    T queue[N];
    size_t begin;
    size_t end;
    size_t size;

    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> stop;

public:
    BankQueue(): begin(0), end(0), size(0) {}

    void enqueue(T element)
    {
        {
            std::unique_lock<std::mutex> lock(this->mtx);

            cv.wait(lock, [this] {
                return this->size < N || stop;
            });

            if(stop) return;

            queue[end] = element;
            end = (end + 1) % N;
            size++;
        }

        cv.notify_one();
    }

    T dequeue()
    {
        std::unique_lock<std::mutex> lock(this->mtx);

        cv.wait(lock, [this] {
            return this->size > 0 || stop;
        });

        if(stop) throw "queue stopped";

        T item = queue[begin];
        begin = (begin + 1) % N;
        size--;

        lock.unlock();
        cv.notify_one();

        return item;
    }

    void stopQueue()
    {
        stop = true;
        cv.notify_all();
    }

    void printQueue()
    {
        {
            std::unique_lock<std::mutex> lock(this->mtx);
            cv.wait(lock, [this]
            {
                return this->getSize() == N || !this->isRunning();
            });

            std::cout << std::endl;
            for(size_t i = 0; i < size; i++)
            {
                std::cout << i << ": " << queue[(begin + i) % N] << std::endl;
            }
            std::cout << std::endl;
        }

        cv.notify_one();
    }

    bool isRunning()
    {
        std::unique_lock<std::mutex> lock(this->mtx);
        return !this->stop.load();
    }

    size_t getSize()
    {   
        std::unique_lock<std::mutex> lock(this->mtx);
        return this->size;
    }

    T getElement(size_t index)
    {
        std::unique_lock<std::mutex> lock(this->mtx);
        return this->queue[index];
    }

    size_t getStart()
    {
        std::unique_lock<std::mutex> lock(this->mtx);
        return this->begin;
    }
};

#endif