#ifndef KRUSKALXPRIM_GRAPH_HPP
#define KRUSKALXPRIM_GRAPH_HPP
#include <iosfwd>
#include <set>
#include <vector>

class Graph {
public:
    /**
     * Represents an edge in the graph.
     */
    struct Edge {
        long a, b;
        long weight;
    };
private:
    std::set<long> vertices;
    std::vector<Edge> edgeList;
public:
    Graph() = default;

    /**
     * Returns the number of vertices in the graph.
     * @return Number of vertices.
     */
    unsigned int getVertexCount() const;

    /**
     * Returns the list of edges in the graph.
     * @return List of edges.
     */
    std::vector<Edge>& getEdgeList() const;

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