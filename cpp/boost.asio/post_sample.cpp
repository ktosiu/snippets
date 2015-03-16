#include <boost/asio.hpp>
#include <iostream>
#include <thread>

boost::asio::io_service io;

void call_back() {
    std::cout << "call back thread: " << std::this_thread::get_id() << std::endl;
    std::cout << "call_back\n";
}

void thread_main() {
    io.run();
}

int main() {
    std::cout << "main thread: " << std::this_thread::get_id() << std::endl;
    io.post(call_back);

    std::thread t(thread_main);
    t.join();
    return 0;
}
