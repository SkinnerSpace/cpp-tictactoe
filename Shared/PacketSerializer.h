#pragma once
#include <cstdint>
#include <vector>

#include "Packet.h"

class PacketSerializer
{
    public:
        static std::vector<std::uint8_t> Serialize(const Packet& packet);
        static Packet Deserialize(const std::vector<std::uint8_t>& bytes);
};
