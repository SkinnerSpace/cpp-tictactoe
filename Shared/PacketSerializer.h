#pragma once
#include <cstdint>
#include <vector>

#include "Packet.h"

class PacketSerializer
{
    public:
        static std::vector<std::uint8_t> serialize(const Packet& packet);
        static Packet deserialize(const std::vector<std::uint8_t>& bytes);
};
