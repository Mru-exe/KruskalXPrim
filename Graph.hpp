#ifndef KRUSKALXPRIM_GRAPH_HPP
#define KRUSKALXPRIM_GRAPH_HPP
#include <iosfwd>
#include <set>

class Graph {
public:
    /**
     * Represents an edge in the graph.
     */
    struct Edge {
        long a, b;
        long weight;

        bool operator==(Edge other) const;

        bool operator<(const Edge& other) const;
    };
private:
    std::set<long> vertices;
    std::set<Edge> edges;
public:
    Graph() = default;

    /**
     * Generates a random connected graph.
     * @param edges the number of edges in the graph.
     * @param maxWeight the maximum edge weight (edge weights will be in the range [0, maxWeight-1]).
     * @return Generated random graph.
     */
    static Graph getRandomGraph(unsigned int edges, unsigned long maxWeight);

    /**
     * Returns the number of vertices in the graph.
     * @return Number of vertices.
     */
    unsigned int getVertexCount() const;

    /**
     * Returns the set of edges in the graph.
     * @return Set of edges.
     */
    const std::set<Edge>& getEdges() const;

    /**
     * Checks if an edge exists between two vertices.
     * @param A One vertex of the edge.
     * @param B The other vertex of the edge.
     * @return True if the edge exists, false otherwise.
     */
    bool hasEdge(long A, long B) const;

    /**
     * Adds an edge to the graph.
     * @param A One veretx of the edge.
     * @param B The other vertex of the edge.
     * @param W The weight of the edge.
     * If the edge already exists, its weight is updated.
     */
    void addEdge(long A, long B, long W);

    /**
     * Prints the graph to the given output stream.
     * @param os Desired output stream.
     * @param simple If true, prints a simplified version.
     */
    void print(std::ostream& os, bool simple = false) const;
};


#endif //KRUSKALXPRIM_GRAPH_HPP