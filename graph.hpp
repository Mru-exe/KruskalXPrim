#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <algorithm>
#include <string>
#include <vector>

/**
 * @brief Vertex, representing a node in a graph.
 *
 * Name: The name of the vertex.
 *
 * Adjacent: A vector of pairs <to_vertex, weight> representing edges to adjacent vertices and their weights.
 */
class vertex {
private:
    std::string name;
    std::vector<std::pair<vertex*, long>> adjacent;
public:
    /**
     * Creates a new vertex with the given name.
     * @param name The name of the vertex
     */
    vertex(std::string name);

    /**
     * Checks if there's an edge to another vertex.
     * @param other The other vertex
     * @return true if there's and edge to the other vertex, false otherwise
     */
    bool is_nei(vertex* other);

    /**
     * Gets the weight of the edge to a neighbouring vertex.
     * @param neighbour The neighbouring vertex
     * @return The weight of the edge to the neighbouring vertex
     */
    long get_cost(vertex* neighbour);

    /**
     * Adds or updates an edge to another vertex with the given weight.
     * @param neighbour The other vertex
     * @param weight The edge weight (default is 0)
     * @return true if the neighbour was added or updated successfully, false otherwise
     */
    bool set_neighbour(vertex* neighbour, long weight = 0);

    /**
     * Removes the directed edge to another vertex.
     * @param neighbour The other vertex
     * @return true if the neighbour was removed successfully, false if it doesn't exist
     */
    bool remove_neighbour(vertex* neighbour);

    /**
     * Gets the name of the vertex.
     * @return The name of the vertex
     */
    std::string get_name() const;
};

#endif //GRAPH_HPP