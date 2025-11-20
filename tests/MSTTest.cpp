#include <iostream>

#include "catch.hpp"
#include "../Graph.hpp"
#include "../MST.hpp"
#include "../UnionFind.hpp"

TEST_CASE("MSTTest - Kruskal") {
    Graph g = Graph::getRandomGraph(100, 50);

    SECTION("MST is Minimal (random graph)") {
        Graph mst;
        mst = MST::kruskal(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdgeList()) {
            UnionFind uf;
            for (auto valid : mst.getEdgeList()) {
                uf.find(valid.a);
                uf.find(valid.b);
                if (removed == valid) {
                    continue;
                }
                uf.unite(valid.a, valid.b);
            }
            REQUIRE(uf.getSetCount() != 1);
        }
    }
}

TEST_CASE("MSTTest - Prim") {
    Graph g = Graph::getRandomGraph(100, 50);

    SECTION("MST is Minimal (random graph)") {
        Graph mst;
        mst = MST::prim(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdgeList()) {
            UnionFind uf;
            for (auto valid : mst.getEdgeList()) {
                uf.find(valid.a);
                uf.find(valid.b);
                if (removed == valid) {
                    continue;
                }
                uf.unite(valid.a, valid.b);
            }
            REQUIRE(uf.getSetCount() != 1);
        }
    }
}