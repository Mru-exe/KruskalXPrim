//
// Created by mru on 20.11.25.
//

#include "MST.hpp"
#include <algorithm>
#include "Graph.hpp"
#include "UnionFind.hpp"

Graph MST::kruskal(const Graph& g) {
    Graph mst;

    std::vector<Graph::Edge> edges = g.getEdgeList();

    //Sort edge list by weight
    std::sort(edges.begin(), edges.end(), [](const Graph::Edge& e1, const Graph::Edge& e2) {
        return e1.weight < e2.weight;
    });

    UnionFind uf;
    for (auto edge : edges) {
        if (uf.find(edge.a) != uf.find(edge.b)) {
            mst.addEdge(edge.a, edge.b, edge.weight);
            uf.unite(edge.a, edge.b);
        }
    }
    return mst;
}

Graph MST::prim(const Graph& g) {
    Graph mst;
    //TODO: Implement Prim's algorithm
    return mst;
}