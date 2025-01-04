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

            std::cout << "Added " << rnd << " to queue" << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(250));            
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
            else
            {
                std::cout << "Failed to add to queue" << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    // Condition to finish queue
    pool.enqueue([&queue] {
        std::this_thread::sleep_for(std::chrono::seconds(20));
        queue.stopQueue();
        std::cout << "Queue was stopped" << std::endl;
    });

    return 0;
}