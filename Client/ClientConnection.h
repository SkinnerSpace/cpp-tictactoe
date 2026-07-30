#pragma once
#include <boost/asio.hpp>
#include <boost/beast/websocket/stream.hpp>

#include "../Shared/PacketSerializer.h"

namespace beast = boost::beast;
namespace websocket = beast::websocket;

class ClientConnection
{
public:
    ClientConnection(boost::asio::io_context& io_context);

    void Connect(const std::string& address, unsigned short port);

    void Send(const Packet& packet);

private:
    void Read();

    websocket::stream<boost::asio::ip::tcp::socket> websocket_;
    beast::flat_buffer buffer_;
};
