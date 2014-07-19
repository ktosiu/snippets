#include <boost/lockfree/spsc_queue.hpp>
#include <thread>
#include <iostream>
#include <atomic>

int producer_count = 0;
std::atomic_int consumer_count(0);
std::atomic<bool> done(false);

boost::lockfree::spsc_queue<int, boost::lockfree::capacity<1024>> spsc_queue;

const int iterations = 1000000;

void producer()
{
    for(int i = 0; i < iterations; i++)
    {
        int value = ++producer_count;
        while(!spsc_queue.push(value));
    }
}

void consumer()
{
    int value;
    while(!done)
    {
        while(spsc_queue.pop(value))
            ++consumer_count;
    }

    while(spsc_queue.pop(value))
        ++consumer_count;
}

int main()
{
    using std::cout;
    cout << "boost::lockfree::spsc_queue is ";
    if(!spsc_queue.is_lock_free())
        cout << "not ";
    cout << "lockfree" << std::endl;

    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    done = true;
    consumer_thread.join();

    cout << "produced " << producer_count << " objects." << std::endl;
    cout << "consumed " << consumer_count << " objects." << std::endl;
    return 0;
}
