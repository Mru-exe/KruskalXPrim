//
// Created by mru on 14.11.25.
//

#include "Graph.hpp"

// ============================================================================
// DSU (Disjoint Set Union) Implementation
// ============================================================================

/**
 * Constructor to initialize DSU with n elements.
 * Initially, each element is in its own set.
 * @param n Number of elements
 */
DSU::DSU(int n) : parent(n), rank(n, 0) {
    // Initially, each element is its own parent (self-loop)
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

/**
 * Find the representative (root) of the set containing element x.
 * Implements path compression optimization.
 * @param x Element to find
 * @return Representative of the set containing x
 */
int DSU::find(int x) {
    // Path compression: make every node on the path point directly to the root
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // Recursively find root and compress path
    }
    return parent[x];
}

/**
 * Union the sets containing elements x and y.
 * Implements union by rank optimization.
 * @param x First element
 * @param y Second element
 */
void DSU::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    // Already in the same set
    if (rootX == rootY) {
        return;
    }
    
    // Union by rank: attach smaller rank tree under root of higher rank tree
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        // If ranks are equal, make one root and increment its rank
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

/**
 * Check if two elements are in the same set.
 * @param x First element
 * @param y Second element
 * @return true if x and y are in the same set, false otherwise
 */
bool DSU::isSameSet(int x, int y) {
    return find(x) == find(y);
}

// ============================================================================
// Graph Implementation
// ============================================================================

/**
 * Constructor to initialize the graph with V vertices.
 * @param vertices Number of vertices in the graph
 */
Graph::Graph(int vertices) : V(vertices), E(0) {
    adjList = new std::vector<std::pair<int, int>>[V];
}

/**
 * Destructor to clean up dynamically allocated memory.
 */
Graph::~Graph() {
    delete[] adjList;
}

/**
 * Copy constructor for deep copying.
 */
Graph::Graph(const Graph& other) : V(other.V), E(other.E), allEdges(other.allEdges) {
    adjList = new std::vector<std::pair<int, int>>[V];
    for (int i = 0; i < V; i++) {
        adjList[i] = other.adjList[i];
    }
}

/**
 * Copy assignment operator.
 */
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        // Clean up existing resources
        delete[] adjList;

        // Copy data
        V = other.V;
        E = other.E;
        allEdges = other.allEdges;

        // Deep copy adjacency list
        adjList = new std::vector<std::pair<int, int>>[V];
        for (int i = 0; i < V; i++) {
            adjList[i] = other.adjList[i];
        }
    }
    return *this;
}

/**
 * Adds an undirected edge to the graph.
 * Updates both adjacency list and edge list.
 * @param src Source vertex
 * @param dest Destination vertex
 * @param weight Weight of the edge
 */
void Graph::addEdge(int src, int dest, int weight) {
    // Add to adjacency list for both directions (undirected graph)
    adjList[src].push_back(std::make_pair(dest, weight));
    adjList[dest].push_back(std::make_pair(src, weight));

    // Add to edge list (only once per edge)
    allEdges.push_back(Edge(src, dest, weight));

    // Increment edge count
    E++;
}

