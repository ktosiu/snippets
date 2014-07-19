#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <atomic>

using std::cout;

std::atomic_int producer_count(0);
std::atomic_int consumer_count(0);
std::atomic<bool> done(false);

boost::lockfree::queue<int> queue(128);
const int iterations = 10000;
const int producer_thread_count = 8;
const int consumer_thread_count = 16;

void producer()
{
    for(int i = 0; i != iterations; i++)
    {
        int value = ++producer_count;
        while(!queue.push(value)) ;
    }
}

void consumer()
{
    int value;
    while(!done)
    {
        while(queue.pop(value))
        {
            ++consumer_count;
        }
    }
    while(queue.pop(value))
    {
        ++consumer_count;
    }
}

int main()
{
    cout << "boost::lockfree::queue is ";
    if(!queue.is_lock_free())
        cout << "not ";
    cout << "lockfree" << std::endl;

    boost::thread_group producer_threads, consumer_threads;

    for(int i = 0; i < producer_thread_count; i++)
        producer_threads.create_thread(producer);

    for(int i = 0; i < consumer_thread_count; i++)
        consumer_threads.create_thread(consumer);

    producer_threads.join_all();
    done = true;
    consumer_threads.join_all();

    cout << "produced " << producer_count << " objects." << std::endl;
    cout << "consumed " << consumer_count << " objects." << std::endl;
}
