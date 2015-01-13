#include <boost/thread.hpp>
#include <iostream>

void task1() { 
    std::cout << "This is task1!\n" << std::endl;
}

void task2() { 
    std::cout << "This is task2!\n" << std::endl;
}

int main (int argc, char ** argv) {
    using namespace boost; 
    thread thread_1 = thread(task1);
    thread thread_2 = thread(task2);

    thread_2.join();
    thread_1.join();
    return 0;
}
