#include "include/generateClients.h"
#include "include/bankQueue.h"
#include "include/threadPool.h"

std::mutex cout_mtx;

#define SAFE_COUT(x) \
    { \
        std::lock_guard<std::mutex> lock(cout_mtx); \
        std::cout <<std::endl << x << std::endl; \
    }

int main(void)
{
    ThreadPool pool(std::thread::hardware_concurrency());

    for(int i = 0; i < 8; i++)
    {
        pool.enqueue([&] {
            std::cout << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }

    return 0;
}