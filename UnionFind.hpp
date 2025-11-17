//
// Created by mru on 17.11.25.
//

#ifndef KRUSKALXPRIM_UNIONFIND_HPP
#define KRUSKALXPRIM_UNIONFIND_HPP
#include <unordered_map>
#include <vector>

/**
 * A Union-Find (Disjoint Set Union) data structure.
 * Only supports integer elements.
 */
class UnionFind {
private:
    std::unordered_map<int, int> parent;
public:
    UnionFind() = default;

    /**
     * Finds the representative of the set containing element x.
     * @param x The element to find.
     * @return The representative of the set containing x.
     */
    int find(int x);

    /**
     * Unites the sets containing elements x and y.
     * @param x An element in the first set.
     * @param y An element in the second set.
     */
    void unite(int x, int y);

    /**
     * Adds a new element to the Union-Find structure.
     * The new element will be in its own set initially.
     * @param x The element to add.
     */
    void addElement(int x);
};


#endif //KRUSKALXPRIM_UNIONFIND_HPP