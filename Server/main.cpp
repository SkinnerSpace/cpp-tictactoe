#include <boost/asio.hpp>
#include <iostream>

int main()
{
    boost::asio::io_context ioContext;

    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::tcp::v4(),
        5000
    );

    boost::asio::ip::tcp::acceptor acceptor(ioContext, endpoint);

    std::cout << "Server is waiting on port 5000...\n";

    boost::asio::ip::tcp::socket socket(ioContext);

    acceptor.accept(socket);

    std::cout << "Client connected.\n";

    return 0;
};
