#include "Server.h"

#include <iostream>
#include <boost/asio.hpp>
#include "../Shared/PacketSerializer.h"

Server::Server(): acceptor(io_context)
{
}

void Server::Run()
{
    const auto port = GetPort();

    const boost::asio::ip::tcp::endpoint endpoint(
            boost::asio::ip::tcp::v4(),
            port
        );

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();

    std::cout << "Server listening on 0.0.0.0:"
              << port << '\n';

    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);

        acceptor.accept(socket);

        auto connection = std::make_shared<ClientConnection>(std::move(socket));

        connections.push_back(connection);

        connection->Start();
    }
}

unsigned short Server::GetPort()
{
    const char* port_value = std::getenv("PORT");

    if (port_value != nullptr)
    {
        return static_cast<unsigned short>(std::stoi(port_value));
    }

    return 5000;
}
