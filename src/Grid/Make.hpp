#pragma once

#include "Grid/IGrid.hpp"
#include "Grid/Grid.hpp"

namespace grid {

template<GridType gt>
Grid make(std::size_t height, std::size_t width);

template<>
Grid make<GridType::Rectangle>(std::size_t height, std::size_t width)
{
    return {height, width};
}

}
