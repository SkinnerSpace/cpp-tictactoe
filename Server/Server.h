#pragma once
#include <string>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "ClientConnection.h"

class Server
{
private:
    int _port;
    std::string _address;

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;

    std::vector<::std::shared_ptr<ClientConnection>> connections;

public:
    Server(std::string address, unsigned short port);
    void Run();
};
