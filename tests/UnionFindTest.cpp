#include "catch.hpp"
#include "../UnionFind.hpp"

TEST_CASE("UnionFind - basic operations") {
    UnionFind uf;

    SECTION("Add 10 elements") {
        REQUIRE_NOTHROW([=](UnionFind uf)
        {
            for (int i = 0; i < 10; ++i) {
                uf.addElement(i);
            }
        });
    }

    SECTION("Each element is in separate set") {
        for (int i = 0; i < 10; ++i) {
            int set = uf.find(i);
            for (int j = 0; j < 10; ++j) {
                if (i==j) continue;
                int otherSet = uf.find(j);
                REQUIRE(set != otherSet);
            }
        }
    }
}

TEST_CASE("UnionFind - advanced operations") {
    UnionFind uf;

    SECTION("Find on new elemts auto-adds") {
        int initial_x = uf.find(10);
        int initial_y = uf.find(20);

        uf.addElement(10);
        uf.addElement(20);

        REQUIRE(initial_x == uf.find(10));
        REQUIRE(initial_y == uf.find(20));
    }

    SECTION("Unite works on added and auto-added") {
        uf.addElement(10);
        uf.addElement(11);

        uf.find(20);
        uf.find(21);

        REQUIRE(uf.find(10) != uf.find(20));
        REQUIRE(uf.find(10) != uf.find(21));
        REQUIRE(uf.find(11) != uf.find(20));
        REQUIRE(uf.find(11) != uf.find(21));

        uf.unite(10, 11);
        REQUIRE(uf.find(10) == uf.find(11));

        uf.unite(20, 21);
        REQUIRE(uf.find(20) == uf.find(21));

        REQUIRE(uf.find(10) != uf.find(20));
        REQUIRE(uf.find(10) != uf.find(21));
        REQUIRE(uf.find(11) != uf.find(20));
        REQUIRE(uf.find(11) != uf.find(21));

        uf.unite(10, 20);
        REQUIRE(uf.find(11) == uf.find(21));
    }
}