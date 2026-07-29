#include "Server.h"
#include <iostream>
#include <boost/asio.hpp>
#include "../Shared/PacketSerializer.h"

Server::Server(std::string address, unsigned short port): acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port))
{
    _address = address;
    _port = port;
}

void Server::Run()
{
    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);

        acceptor.accept(socket);

        auto connection = std::make_shared<ClientConnection>(std::move(socket));

        connections.push_back(connection);

        connection->Start();
    }

    boost::asio::io_context io_context;

    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::make_address(_address),
        _port
    );

    std::cout << "Server is waiting on port 5000...\n";

    boost::asio::ip::tcp::socket socket(io_context);

    acceptor.accept(socket);

    std::cout << "Client connected.\n";

    std::string welcome_message = "Welcome";

    Packet packet{PacketType::Message};
    packet.payload.assign(welcome_message.begin(), welcome_message.end());
    packet.length = packet.payload.size();

    auto serialized_packet = PacketSerializer::serialize(packet);

    boost::asio::write(socket, boost::asio::buffer(serialized_packet));

    socket.close();
}
