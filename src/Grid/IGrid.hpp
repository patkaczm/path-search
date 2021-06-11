#include <vector>
#include <set>
#include "Grid/Cell.hpp"

namespace grid {

enum class GridType {
    Rectangle,
};

//temporary name, when ThickWallsRectangleGrid is implemented change to Grid
class IGrid {
public:
    virtual ~IGrid() = default;

    virtual Cell at(std::size_t j, std::size_t i) const = 0;
    virtual std::pair<std::size_t, std::size_t> size() const = 0;
    virtual std::set<Cell> adjacent(const Cell& c) const = 0;

    virtual std::vector<int> flat() const = 0;
};

}
