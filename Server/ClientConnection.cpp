#include "ClientConnection.h"
#include <iostream>
#include <boost/asio.hpp>
#include "../Shared/PacketSerializer.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket&& socket): _socket(std::move(socket))
{
    auto ip = _socket.remote_endpoint().address().to_string();
}

void ClientConnection::Start()
{
    while (true)
    {
        Packet packet;

        boost::system::error_code error;

        boost::asio::read(
            socket,
            boost::asio::buffer(&packet.length, sizeof(packet.length)),
            error
        );

        if (error == boost::asio::error::eof)
        {
            std::cout << "Client disconnected.\n";
            break;
        }

        if (error)
        {
            std::cout << "Read error: " << error.message() << "\n";
            break;
        }

        boost::asio::read(
            socket,
            boost::asio::buffer(&packet.type, sizeof(packet.type)));

        boost::asio::read(
            socket,
            boost::asio::buffer(packet.payload.data(), packet.payload.size()));

        packet.payload.resize(packet.length);

        boost::asio::read(
            socket, boost::asio::buffer(packet.payload)
        );

        if (packet.type == PacketType::Disconnect)
        {
            break;
        }
    }
}

