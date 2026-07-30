#include <fstream>
#include <boost/asio.hpp>
#include <iostream>

#include "Server.h"

int main()
{
    std::string address;
    unsigned short port = 0;

    try
    {
        std::ifstream config_file("server.conf");

        if (!config_file.is_open())
        {
            throw std::runtime_error("Could not open server.conf");
        }

        std::string line;

        while (std::getline(config_file, line))
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

    Server server();

    return 0;
};


