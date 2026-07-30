#include "ClientConnection.h"
#include <iostream>
#include <boost/asio.hpp>
#include "../Shared/PacketSerializer.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket&& socket): websocket(std::move(socket))
{
    boost::system::error_code error;

    const auto endpoint = websocket.next_layer().remote_endpoint(error);

    if (error)
    {
        std::cerr
            << "Could not get client endpoint: "
            << error.message()
            << '\n';

        return;
    }

    const auto ip = endpoint.address().to_string();

    std::cout << "Client connected: " << ip << '\n';
}

void ClientConnection::Start()
{
    boost::system::error_code error;

    websocket.accept(error);

    if (error)
    {
        std::cout << "Handshake failed: "
                  << error.message() << "\n";
        return;
    }

    beast::flat_buffer buffer;

    while (true)
    {
        websocket.read(buffer, error);

        if (error == websocket::error::closed)
        {
            std::cout << "Client closed the WebSocket connection.\n";
            break;
        }

        if (error)
        {
            std::cout << "WebSocket read error: " << error.message() << '\n';
            break;
        }

        std::vector<uint8_t> bytes(
            boost::asio::buffers_begin(buffer.data()),
            boost::asio::buffers_end(buffer.data())
        );

        buffer.consume(buffer.size());

        auto packet = PacketSerializer::Deserialize(bytes);

        std::string text(packet.payload.begin(), packet.payload.end());

        std::cout << text << std::endl;
    }
}

