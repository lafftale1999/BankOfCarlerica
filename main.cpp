#include "include/generateClients.h"
#include "include/bankQueue.h"
#include "include/threadPool.h"

int main(void)
{
    ThreadPool pool(std::thread::hardware_concurrency());

    BankQueue<int,10> queue;

    // Add people to queue
    pool.enqueue([&queue] {
        while(queue.isRunning())
        {
            int rnd = rand() % 100;
            queue.enqueue(rnd);

            std::cout << "Added " << rnd << " from queue" << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));            
        }
    });

    // Remove people from queue
    pool.enqueue([&queue] {
        while(queue.isRunning())
        {
            auto item = queue.dequeue();
            if(item)
            {
                std::cout << "Removed " << *item << " from queue" << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    // Condition to finish queue
    pool.enqueue([&queue] {
        std::this_thread::sleep_for(std::chrono::seconds(20));
        queue.stopQueue();
    });

    return 0;
}