#include <boost/asio.hpp>
#include <iostream>

int main()
{
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::socket socket(io_context);

    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::make_address("127.0.0.1"),
        5000
    );

    socket.connect(endpoint);

    std::cout << "Connected to server.\n";

    return 0;
}
