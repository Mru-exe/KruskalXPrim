#include "catch.hpp"
#include "../UnionFind.hpp"

TEST_CASE("UnionFind - basic operations") {
    UnionFind uf;

    SECTION("Add 10 elements") {
        REQUIRE_NOTHROW([](UnionFind& ufp)
        {
            for (int i = 0; i < 10; ++i) {
                ufp.addElement(i);
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

    SECTION("Disjoint set count is equal to 10") {
        for (int i = 0; i < 10; ++i) {
            uf.addElement(i);
        }
        unsigned int count = uf.getSetCount();
        REQUIRE(count == 10);
    }
}

TEST_CASE("UnionFind - advanced operations") {
    UnionFind uf;

    uf.addElement(10);
    uf.addElement(11);

    uf.find(20);
    uf.find(21);

    SECTION("Find on new elemts auto-adds") {
        int initial_x = uf.find(321);
        int initial_y = uf.find(123);

        uf.addElement(321);
        uf.addElement(123);

        REQUIRE(initial_x == uf.find(321));
        REQUIRE(initial_y == uf.find(123));
    }

    SECTION("Unite works on added and auto-added") {
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

    SECTION("After union, only 1 set is left") {
        uf.unite(10, 11);
        uf.unite(20, 21);
        uf.unite(10, 20);
        unsigned int count = uf.getSetCount();
        REQUIRE(count == 1);
    }
}