#include "ClientConnection.h"
#include <boost/beast/core.hpp>

#include <iostream>
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

ClientConnection::ClientConnection(boost::asio::io_context& io_context): websocket_(io_context)
{
}

void ClientConnection::Connect(const std::string& address, unsigned short port)
{
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::make_address(address),
        port
    );

    websocket_.next_layer().connect(endpoint);
    websocket_.handshake(address, "/");

    std::cout << "Connected to server.\n";

    boost::system::error_code error;

    beast::flat_buffer buffer;

    while (true)
    {
        websocket_.read(buffer, error);

        if (error == websocket::error::closed)
        {
            std::cout << "Server closed the WebSocket connection.\n";
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

        Packet packet = PacketSerializer::Deserialize(bytes);
    }

    websocket_.close(websocket::close_code::normal);
}

void ClientConnection::Send(const Packet& packet)
{
    auto serialized_packet = PacketSerializer::Serialize(packet);

    websocket_.write(boost::asio::buffer(serialized_packet));
}

void ClientConnection::Read()
{
    websocket_.async_read(
       buffer_,
       [this](
           const boost::system::error_code& error,
           std::size_t bytesTransferred)
       {
           if (error == websocket::error::closed)
           {
               std::cout << "Server closed the connection.\n";
               return;
           }

           if (error)
           {
               std::cout
                   << "Read error: "
                   << error.message()
                   << '\n';
               return;
           }

           std::vector<std::uint8_t> bytes(
               boost::asio::buffers_begin(buffer_.data()),
               boost::asio::buffers_end(buffer_.data())
           );

           buffer_.consume(buffer_.size());

           Packet packet =
               PacketSerializer::Deserialize(bytes);

           std::cout << "Received " << bytes.size() << " bytes.\n";

           Read();
       });
}
