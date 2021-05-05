#include "Backend/Cell.hpp"

#include <map>

namespace Grid {

Cell::Cell(int id, int type) : id(id), type(toType(type))
{
}

Cell::Type Cell::toType(int type) const
{
    static const std::map<int, Cell::Type> converter {{0, Cell::Type::EmptyField}, {1, Cell::Type::Start},
                                                     {2, Cell::Type::End}, {3, Cell::Type::Obstacle}};
    return converter.at(type);
}

}
