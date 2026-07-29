#pragma once
#include <cstdint>

enum class PacketType : std::uint8_t
{
    Hello = 1,
    Message = 2,
    Disconnect = 3,
};
