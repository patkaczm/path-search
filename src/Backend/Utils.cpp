#include "Backend/Utils.hpp"

namespace utils {

graph::Graph makeGraph(const grid::Grid &grid)
{
    graph::Graph graph;
    //add vertexes
    for (const auto& row : grid.getRows()) {
        for (const auto& cell : row) {
            graph.add(graph::Vertex{cell.id});
        }
    }
    auto plane = grid.getRows();
    //add edges
    for (int i = 0 ; i < plane.size(); i++) {
        for (int j = 0 ; j < plane[i].size(); j++) {
            if (plane[i][j].type == grid::Cell::Type::Obstacle) {
                continue;
            }
            if (i > 0) {
                if (plane[i-1][j].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i-1][j].id}});
                }
            }
            if (j < plane[i].size() - 1) {
                if (plane[i][j + 1].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i][j + 1].id}});
                }
            }
            if (i < plane.size() - 1) {
                if (plane[i + 1][j].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i + 1][j].id}});
                }
            }
            if (j > 0 ) {
                if (plane[i][j - 1].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i][j - 1].id}});
                }
            }
        }
    }
    return graph;
}

}
