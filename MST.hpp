#ifndef KRUSKALXPRIM_MSTALGORITHMS_HPP
#define KRUSKALXPRIM_MSTALGORITHMS_HPP

#include "Graph.hpp"

namespace MST
{
    /**
     * Performs Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a given graph.
     * @param g The input graph.
     * @return Sub-graph of g representing the MST
     */
    Graph kruskal(const Graph& g);

    /**
     * Performs Prim's algorithm to find the Minimum Spanning Tree (MST) of a given graph.
     * @param g The input graph.
     * @return Sub-graph of g representing the MST
     */
    Graph prim(const Graph& g);
}

#endif //KRUSKALXPRIM_MSTALGORITHMS_HPP