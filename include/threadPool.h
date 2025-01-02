#ifndef __MY_THREAD_POOL_H
#define __MY_THREAD_POOL_H

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>

class ThreadPool
{
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    
    std::mutex mtx;
    std::condition_variable cv;

    std::atomic<bool> stop;

public:
    ThreadPool(size_t numThreads): stop(false)
    {
        for(size_t i = 0; i < numThreads; i++)
        {
            workers.emplace_back([this]
            {
                while(1)
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this]
                    {
                        return stop || !tasks.empty();
                    });

                    if(stop && tasks.empty()) return;

                    auto task = std::move(tasks.front());
                    tasks.pop();

                    lock.unlock();

                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }

        cv.notify_all();

        for(auto& t : workers)
        {
            if(t.joinable()) t.join();
        }
    }

    template<class F>
    void enqueue(F&& task)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::forward<F>(task));
        }
        cv.notify_one();
    }
};

#endif