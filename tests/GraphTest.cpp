#include <iostream>

#include "catch.hpp"
#include "../Graph.hpp"
#include "../UnionFind.hpp"


TEST_CASE("Graph - Basic behaviour") {
    Graph g;
    SECTION("Triangle graph") {
        g.addEdge(1, 2, 10);
        g.addEdge(2, 3, 20);
        g.addEdge(3, 1, 30);

        REQUIRE(g.getVertexCount() == 3);
        REQUIRE(g.getEdgeList().size() == 3);
    }

    SECTION("AddEdge overrides existing") {
        g.addEdge(1, 2, 10);
        g.addEdge(3, 4, 20);

        long vcount = g.getVertexCount();
        long ecount = g.getEdgeList().size();
        REQUIRE(vcount == 4);
        REQUIRE(ecount == 2);

        for (auto edge : g.getEdgeList()) {
            long newWeight = edge.weight + 5;
            g.addEdge(edge.a, edge.b, newWeight);

            REQUIRE(g.getEdgeList().size() == ecount);
            REQUIRE(g.getVertexCount() == vcount);
        }
    }
}

TEST_CASE("Graph - Simple generation") {
    Graph g;
    srand(Catch::rngSeed());
    SECTION("20 Random Edges") {
        long A,B,W;
        for (int i = 0; i < 20; ++i) {
            A = rand() % 20;
            B = rand() % 20;
            W = rand() % 100;

            g.addEdge(A, B, W);
        }
        long edges = g.getEdgeList().size();
        REQUIRE(edges <= 20);
    }

    SECTION("Generating until connected") {
        UnionFind uf;
        long A,B,W;
        do {
            A = rand() % 100;
            B = rand() % 100;
            W = rand() % 50;
            g.addEdge(A, B, W);
            uf.unite(A, B);
        } while (uf.getSetCount() != 1 || g.getVertexCount() < 5);
        REQUIRE(uf.getSetCount() == 1);
    }
}

TEST_CASE("Graph - Advanced generation") {
    SECTION("20 random graphs - Modulo 400") {
        for (int i = 0; i < 20; ++i) {
            Graph g;
            UnionFind uf;
            long A,B,W;
            do {
                A = rand() % 400;
                B = rand() % 400;
                W = rand() % 50;
                g.addEdge(A, B, W);
                uf.unite(A, B);
            } while (uf.getSetCount() != 1 || g.getEdgeList().size() < 5);

            //Must not be greater than 1
            REQUIRE_FALSE(uf.getSetCount() > 1);
            REQUIRE(g.getEdgeList().size() >= 5);
        }
    }

    SECTION("5000 random graphs - Modulo 50") {
        for (int i = 0; i < 5000; ++i) {
            Graph g;
            UnionFind uf;
            long A,B,W;
            do {
                A = rand() % 50;
                B = rand() % 50;
                W = rand() % 50;
                g.addEdge(A, B, W);
                uf.unite(A, B);
            } while (uf.getSetCount() != 1 || g.getEdgeList().size() < 5);

            //Must not be greater than 1
            REQUIRE_FALSE(uf.getSetCount() > 1);
            REQUIRE(g.getEdgeList().size() >= 5);
        }
    }
}