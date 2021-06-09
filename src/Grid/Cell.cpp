#include "Grid/Cell.hpp"

#include <map>

namespace grid {

Cell::Cell(uint32_t id) : id(id), type(Type::EmptyField)
{
}

Cell::Cell(std::uint32_t id, std::uint8_t type) : id(id), type(toType(type))
{
}

Cell::Cell(uint32_t id, Cell::Type type) : id (id), type(type)
{
}

bool Cell::operator==(const Cell &rhs) const
{
    return id == rhs.id && type == rhs.type;
}

bool Cell::operator<(const Cell &rhs) const
{
    return id < rhs.id;
}

Cell::Type Cell::toType(std::uint8_t type) const
{
    static const std::map<std::uint8_t, Cell::Type> converter {{0, Cell::Type::EmptyField}, {1, Cell::Type::Start},
                                                     {2, Cell::Type::End}, {3, Cell::Type::Obstacle}};
    return converter.at(type);
}

}
