#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <thread>

boost::asio::io_service io;

void print(const boost::system::error_code& /*e*/)
{
    std::cout << "timer thread: " << std::this_thread::get_id() << " ";
    std::cout << "Hello, world!\n";
}

void thread_main()
{
    io.run();
}

int main()
{
    std::cout << "main thread: " << std::this_thread::get_id() << std::endl;
    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(5));
    timer.async_wait(&print);
    std::thread t(thread_main);
    t.join();
    return 0;
}
