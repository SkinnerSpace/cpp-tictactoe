#include "PacketSerializer.h"

#include <stdexcept>

std::vector<std::uint8_t> PacketSerializer::Serialize(const Packet& packet)
{
    std::vector<std::uint8_t> bytes;

    bytes.reserve(packet.payload.size() + 1);

    bytes.push_back(static_cast<std::uint8_t>(packet.type));

    bytes.insert(bytes.end(), packet.payload.begin(), packet.payload.end());
}

Packet PacketSerializer::Deserialize(const std::vector<std::uint8_t>& bytes)
{
    if (bytes.empty())
    {
        throw std::runtime_error(
            "Cannot deserialize an empty packet"
        );
    }

    Packet packet{};

    packet.type = static_cast<PacketType>(bytes[0]);

    packet.payload.assign(bytes.begin() + 1, bytes.end());

    return packet;
}
