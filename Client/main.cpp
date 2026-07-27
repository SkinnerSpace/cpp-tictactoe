#include <fstream>
#include <boost/asio.hpp>
#include <iostream>

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

    std::string message = "hello";

    boost::asio::write(socket, boost::asio::buffer(message));

    return 0;
}
