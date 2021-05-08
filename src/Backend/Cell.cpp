#include "Backend/Cell.hpp"

#include <map>

namespace grid {

Cell::Cell(std::uint32_t id, std::uint8_t type) : id(id), type(toType(type))
{
}

Cell::Type Cell::toType(std::uint8_t type) const
{
    static const std::map<std::uint8_t, Cell::Type> converter {{0, Cell::Type::EmptyField}, {1, Cell::Type::Start},
                                                     {2, Cell::Type::End}, {3, Cell::Type::Obstacle}};
    return converter.at(type);
}

}
