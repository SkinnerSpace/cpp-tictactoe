#pragma once
#include <boost/asio/ip/tcp.hpp>

class ClientConnection
{
private:
    boost::asio::ip::tcp::socket _socket;

public:
    ClientConnection(boost::asio::ip::tcp::socket&& socket);
    void Start();
};
