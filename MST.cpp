//
// Created by mru on 20.11.25.
//

#include "MST.hpp"
#include <algorithm>
#include <queue>
#include <map>
#include <set>
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

    if (g.getVertexCount() == 0) {
        return mst;
    }

    std::vector<Graph::Edge> edges = g.getEdgeList();

    std::map<long, std::vector<std::pair<long, long>>> adjList;
    std::set<long> allVertices;

    for (const auto& edge : edges) {
        adjList[edge.a].emplace_back(edge.b, edge.weight);
        adjList[edge.b].emplace_back(edge.a, edge.weight);
        allVertices.insert(edge.a);
        allVertices.insert(edge.b);
    }

    if (allVertices.size() <= 1) {
        return mst;
    }

    std::priority_queue<std::pair<long, std::pair<long, long>>,
                        std::vector<std::pair<long, std::pair<long, long>>>,
                        std::greater<std::pair<long, std::pair<long, long>>>> pq;

    std::set<long> visited;

    long startVertex = *allVertices.begin();
    visited.insert(startVertex);

    for (const auto& neighbor : adjList[startVertex]) {
        pq.push({neighbor.second, {startVertex, neighbor.first}});
    }

    while (!pq.empty() && visited.size() < allVertices.size()) {
        auto [weight, vertices] = pq.top();
        pq.pop();

        auto [from, to] = vertices;

        if (visited.find(to) != visited.end()) {
            continue;
        }

        mst.addEdge(from, to, weight);
        visited.insert(to);

        for (const auto& neighbor : adjList[to]) {
            if (visited.find(neighbor.first) == visited.end()) {
                pq.push({neighbor.second, {to, neighbor.first}});
            }
        }
    }
    return mst;
}