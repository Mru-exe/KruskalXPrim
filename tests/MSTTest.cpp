#include <iostream>

#include "catch.hpp"
#include "../Graph.hpp"
#include "../MST.hpp"
#include "../UnionFind.hpp"

TEST_CASE("MSTTest - Kruskal") {
    SECTION("MST is minimal (Tree)") {
        Graph tree;
        unsigned int vertexCount = 100;

        for (int i=0; i<vertexCount; ++i) {
            if (2*i+1 < vertexCount) {
                tree.addEdge(i, 2*i+1, 1);
            }
            if (2*i+2 < vertexCount) {
                tree.addEdge(i, 2*i+2, 1);
            }
        }
        Graph mst = MST::kruskal(tree);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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

    SECTION("MST is minimal (Line graph)") {
        Graph minimal;
        unsigned int vertexCount = 100;
        for (unsigned int i = 0; i < vertexCount - 1; ++i) {
            minimal.addEdge(i, i + 1, 1);
        }

        Graph mst = MST::kruskal(minimal);
        REQUIRE(mst.getEdges().size() == vertexCount - 1); //Is line

        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
                uf.find(valid.a);
                uf.find(valid.b);
                if (removed == valid) {
                    continue;
                }
                uf.unite(valid.a, valid.b);
            }
            REQUIRE(uf.getSetCount() != 1); //Is Minimal
        }

    }

    SECTION("MST is minimal (Complete graph)") {
        Graph complete;
        unsigned int vertexCount = 100;
        for (unsigned int i = 0; i < vertexCount; ++i) {
            for (unsigned int j = i + 1; j < vertexCount; ++j) {
                if (i==j) continue;
                complete.addEdge(i, j, i+j%20);
            }
        }

        Graph mst = MST::kruskal(complete);

        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
                uf.find(valid.a);
                uf.find(valid.b);
                if (removed == valid) {
                    continue;
                }
                uf.unite(valid.a, valid.b);
            }
            REQUIRE(uf.getSetCount() != 1); //Is Minimal
        }
    }

    SECTION("MST is minimal (Random graph - 100 edges)") {
        Graph mst;
        Graph g = Graph::getRandomGraph(100, 200);
        mst = MST::kruskal(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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

    SECTION("MST is minimal (Random graph - 1000 edges)") {
        Graph mst;
        Graph g = Graph::getRandomGraph(1000, 200);
        mst = MST::kruskal(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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

    SECTION("MST is minimal (Random graph - 10 000 edges)") {
        Graph mst;
        Graph g = Graph::getRandomGraph(10000, 200);
        mst = MST::kruskal(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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
    SECTION("MST is minimal (Tree)") {
        Graph tree;
        unsigned int vertexCount = 100;

        for (int i=0; i<vertexCount; ++i) {
            if (2*i+1 < vertexCount) {
                tree.addEdge(i, 2*i+1, 1);
            }
            if (2*i+2 < vertexCount) {
                tree.addEdge(i, 2*i+2, 1);
            }
        }
        Graph mst = MST::prim(tree);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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

    SECTION("MST is minimal (Line graph)") {
        Graph minimal;
        unsigned int vertexCount = 100;
        for (unsigned int i = 0; i < vertexCount - 1; ++i) {
            minimal.addEdge(i, i + 1, 1);
        }

        Graph mst = MST::prim(minimal);
        REQUIRE(mst.getEdges().size() == vertexCount - 1); //Is line

        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
                uf.find(valid.a);
                uf.find(valid.b);
                if (removed == valid) {
                    continue;
                }
                uf.unite(valid.a, valid.b);
            }
            REQUIRE(uf.getSetCount() != 1); //Is Minimal
        }

    }

    SECTION("MST is minimal (Complete graph)") {
        Graph complete;
        unsigned int vertexCount = 100;
        for (unsigned int i = 0; i < vertexCount; ++i) {
            for (unsigned int j = i + 1; j < vertexCount; ++j) {
                if (i==j) continue;
                complete.addEdge(i, j, i+j%20);
            }
        }

        Graph mst = MST::prim(complete);

        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
                uf.find(valid.a);
                uf.find(valid.b);
                if (removed == valid) {
                    continue;
                }
                uf.unite(valid.a, valid.b);
            }
            REQUIRE(uf.getSetCount() != 1); //Is Minimal
        }
    }

    SECTION("MST is minimal (Random graph - 100 edges)") {
        Graph g = Graph::getRandomGraph(100, 200);
        Graph mst;
        mst = MST::prim(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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

    SECTION("MST is minimal (Random graph - 1000 edges)") {
        Graph g = Graph::getRandomGraph(1000, 200);
        Graph mst;
        mst = MST::prim(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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

    SECTION("MST is minimal (Random graph - 10 000 edges)") {
        Graph g = Graph::getRandomGraph(10000, 200);
        Graph mst;
        mst = MST::prim(g);

        //For each edge, removing it should increase the number of components
        for (auto removed : mst.getEdges()) {
            UnionFind uf;
            for (auto valid : mst.getEdges()) {
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