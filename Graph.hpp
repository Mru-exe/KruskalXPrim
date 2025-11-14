//
// Created by mru on 14.11.25.
//

#ifndef KRUSKALXPRIM_GRAPH_HPP
#define KRUSKALXPRIM_GRAPH_HPP

#include <vector>
#include <utility>

/**
 * Structure to represent an edge in the graph.
 * Used primarily for Kruskal's algorithm.
 */
struct Edge {
    int src;    // Source vertex
    int dest;   // Destination vertex
    int weight; // Weight of the edge

    // Constructor for convenience
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

/**
 * Disjoint Set Union (DSU) / Union-Find data structure.
 * Used for efficient cycle detection in Kruskal's algorithm.
 * Implements path compression and union by rank optimizations.
 */
class DSU {
private:
    std::vector<int> parent;  // Parent array for each element
    std::vector<int> rank;    // Rank (approximate tree height) for each set

public:
    /**
     * Constructor to initialize DSU with n elements.
     * Initially, each element is in its own set.
     * @param n Number of elements
     */
    explicit DSU(int n);

    /**
     * Find the representative (root) of the set containing element x.
     * Implements path compression optimization.
     * @param x Element to find
     * @return Representative of the set containing x
     */
    int find(int x);

    /**
     * Union the sets containing elements x and y.
     * Implements union by rank optimization.
     * @param x First element
     * @param y Second element
     */
    void unionSets(int x, int y);

    /**
     * Check if two elements are in the same set.
     * @param x First element
     * @param y Second element
     * @return true if x and y are in the same set, false otherwise
     */
    bool isSameSet(int x, int y);
};

/**
 * Class to represent a weighted, undirected graph.
 * Uses adjacency list for efficient traversal (Prim's algorithm)
 * and edge list for Kruskal's algorithm.
 */
class Graph {
private:
    int V;  // Number of vertices
    int E;  // Number of edges
    std::vector<std::pair<int, int>>* adjList;  // Adjacency list: adjList[v] contains pairs of <destination, weight>
    std::vector<Edge> allEdges;  // List of all edges for Kruskal's algorithm

public:
    /**
     * Constructor to initialize the graph with V vertices.
     * @param vertices Number of vertices in the graph
     */
    explicit Graph(int vertices = 0);

    /**
     * Destructor to clean up dynamically allocated memory.
     */
    ~Graph();

    /**
     * Copy constructor for deep copying.
     */
    Graph(const Graph& other);

    /**
     * Copy assignment operator.
     */
    Graph& operator=(const Graph& other);

    /**
     * Adds an undirected edge to the graph.
     * Updates both adjacency list and edge list.
     * @param src Source vertex
     * @param dest Destination vertex
     * @param weight Weight of the edge
     */
    void addEdge(int src, int dest, int weight);

    /**
     * Gets the number of vertices in the graph.
     * @return Number of vertices
     */
    int getVertices() const { return V; }

    /**
     * Gets the number of edges in the graph.
     * @return Number of edges
     */
    int getEdges() const { return E; }

    /**
     * Gets the adjacency list.
     * @return Pointer to the adjacency list array
     */
    const std::vector<std::pair<int, int>>* getAdjList() const { return adjList; }

    /**
     * Gets all edges in the graph.
     * @return Vector containing all edges
     */
    const std::vector<Edge>& getAllEdges() const { return allEdges; }
};

#endif //KRUSKALXPRIM_GRAPH_HPP