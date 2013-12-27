#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

void accept_handler(const boost::system::error_code &ec)
{
  if (!ec)
  {
      boost::asio::async_write(sock, boost::asio::buffer(data), write_handler);
  }
}

int main()
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT);
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
    boost::asio::ip::tcp::socket sock(io_service);
    io_service.run();
}
