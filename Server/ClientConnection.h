#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class ClientConnection
{
private:
    websocket::stream<tcp::socket> websocket;

public:
    ClientConnection(boost::asio::ip::tcp::socket&& socket);
    void Start();
};
