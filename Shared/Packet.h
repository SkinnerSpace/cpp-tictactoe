#pragma once
#include <vector>
#include "PacketType.h"

struct Packet
{
    PacketType type;
    std::vector<std::uint8_t> payload;
    uint32_t length;
};
