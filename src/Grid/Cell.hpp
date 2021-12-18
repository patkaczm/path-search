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

    Cell() = default;
    explicit Cell(std::uint32_t id);
    Cell(std::uint32_t id, std::uint8_t type);
    Cell(std::uint32_t id, Type type);

    std::uint32_t id;
    Type type;
    bool operator==(const Cell& rhs) const;
    bool operator<(const Cell& rhs) const;
private:
    Type toType(std::uint8_t type) const;
};

}
