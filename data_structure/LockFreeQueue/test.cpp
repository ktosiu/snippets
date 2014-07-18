#include "LockFreeQueue.h"
#include <stdio.h>
#include <thread>

LockFreeQueue<int> lock_free_queue;

void producer()
{
    int count = 0;
    while(true)
    {
        lock_free_queue.Produce(count);
        count++;
    }
}

void consumer()
{
    while(true)
    {
        int item = 0;
        if(lock_free_queue.Consume(item))
        {
            printf("consumed: %d\n", item);
        }
    }
}

int main()
{
    try
    {
        std::thread producer_thread(&producer);
        std::thread consumer_thread(&consumer);
        producer_thread.join();
        consumer_thread.join();
    } catch(std::exception& e)
    {
        printf("%s\n", e.what());
    }
}
