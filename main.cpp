#include "include/generateClients.h"
#include "include/bankQueue.h"

std::mutex cout_mtx;

#define SAFE_COUT(x) \
    { \
        std::lock_guard<std::mutex> lock(cout_mtx); \
        std::cout <<std::endl << x << std::endl; \
    }

int main(void)
{
    return 0;
}