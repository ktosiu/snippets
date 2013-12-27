#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main()
{
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(boost::asio::ip::host_name(),"");
    tcp::resolver::iterator it=resolver.resolve(query);

    while(it!=tcp::resolver::iterator())
    {
        boost::asio::ip::address addr=(it++)->endpoint().address();
        if(addr.is_v6())
        {
            std::cout<<"ipv6 address: ";
        }
        else
            std::cout<<"ipv4 address: ";

        std::cout<<addr.to_string()<<std::endl;
    }
}
