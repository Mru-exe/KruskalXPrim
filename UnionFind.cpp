#include "UnionFind.hpp"

#include <set>

long UnionFind::find(long x) {
    // If x is not in the parent map, add it as its own parent
    if (parent.find(x) == parent.end()) {
        parent[x] = x;
        return x;
    }

    // Path compression: make every node on the path point directly to the root
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }

    return parent[x];
}

void UnionFind::unite(long x, long y) {
    // Find representatives of both sets
    long rootX = find(x);
    long rootY = find(y);

    // If they're already in the same set, nothing to do
    if (rootX == rootY) {
        return;
    }

    // Union by making one root point to the other
    parent[rootX] = rootY;
}

void UnionFind::addElement(long x) {
    // Only add if not already present
    if (parent.find(x) == parent.end()) {
        parent[x] = x;
    }
}

unsigned long UnionFind::getSetCount() {
    std::set<long> uniqueRoots;
    for (auto set : parent) {
        uniqueRoots.insert(find(set.first));
    }
    return uniqueRoots.size();
}
