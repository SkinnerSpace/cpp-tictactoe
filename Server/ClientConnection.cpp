#include "ClientConnection.h"
#include <iostream>
#include <boost/asio.hpp>
#include "../Shared/PacketSerializer.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket&& socket): websocket(std::move(socket))
{
    auto ip = socket.remote_endpoint().address().to_string();
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
    }
}

