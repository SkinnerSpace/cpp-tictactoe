#include <fstream>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/beast/websocket/stream.hpp>

#include "ClientConnection.h"
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;


#include "../Shared/PacketSerializer.h"

int main()
{
    std::string address;
    unsigned short port = 0;

    try
    {
        std::ifstream configFile("client.conf");

        if (!configFile.is_open())
        {
            throw std::runtime_error("Could not open server.conf");
        }

        std::string line;

        while (std::getline(configFile, line))
        {
            const std::size_t separation_position = line.find("=");

            if (separation_position == std::string::npos)
            {
                continue;
            }

            const std::string key = line.substr(0, separation_position);
            const std::string value = line.substr(separation_position + 1);

            if (key == "address")
            {
                address = value;
            }

            if (key == "port")
            {
                port = static_cast<unsigned short>(std::stoi(value));
            }
        }
    }catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    boost::asio::io_context io_context;

    ClientConnection client_connection{io_context};

    client_connection.Connect(address, port);

    std::string welcome_message = "Connected";

    Packet packet{PacketType::Message};
    packet.payload.assign(welcome_message.begin(), welcome_message.end());

    client_connection.Send(packet);
}
