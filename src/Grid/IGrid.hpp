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
    struct Size {
        std::size_t height;
        std::size_t width;
    };

    virtual ~IGrid() = default;

    virtual Cell at(std::size_t j, std::size_t i) const = 0;
    virtual Size size() const = 0;
    virtual std::set<Cell> adjacent(const Cell& c) const = 0;

    virtual std::vector<int> flat() const = 0;
};

}
