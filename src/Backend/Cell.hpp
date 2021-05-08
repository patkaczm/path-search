#pragma once

#include <cstdint>

namespace grid {

struct Cell {
    enum class Type : std::uint8_t {
        EmptyField = 0,
        Start,
        End,
        Obstacle,
    };

    Cell(std::uint32_t id, std::uint8_t type);

    std::uint32_t id;
    Type type;
private:
    Type toType(std::uint8_t type) const;
};

}
