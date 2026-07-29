#include <fstream>
#include <boost/asio.hpp>
#include <iostream>
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

    boost::asio::ip::tcp::socket socket(io_context);

    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::make_address(address),
        port
    );

    socket.connect(endpoint);

    std::cout << "Connected to server.\n";

    std::string welcome_message = "Connected";

    Packet packet{PacketType::Message};
    packet.payload.assign(welcome_message.begin(), welcome_message.end());
    packet.length = packet.payload.size();

    auto serialized_packet = PacketSerializer::serialize(packet);

    boost::asio::write(socket, boost::asio::buffer(serialized_packet));

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
            std::cout << "Server is unavailable.\n";
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

    socket.close();

    return 0;
}
