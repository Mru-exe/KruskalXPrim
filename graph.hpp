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
     * @return true if there's an edge to the other vertex, false otherwise
     */
    bool is_neighbour(vertex* other);

    /**
     * Gets all adjacent vertices and their edge weights.
     * @return Returns the adjacent vertices and their edge weights.
     */
    std::vector<std::pair<vertex*, long>> get_neighbours();

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

/**
 * @brief Graph, representing a collection of vertices and edges.
 * vertices: A vector of vertices in the graph.
 * edge_count: The total number of edges in the graph.
 */
class graph {
private:
    std::vector<vertex> vertices;
    unsigned long edge_count = 0;
public:
    graph()= default;

    /**
     * Creates and adds a new vertex to the graph.
     * @param name The name of the vertex
     * @throws std::invalid_argument if a vertex with the same name already exists
     */
    void add_vertex(const std::string& name);

    /**
     * Adds a new vertex to the graph.
     * @param v The vertex to add
     * @throws std::invalid_argument if a vertex with the same name already exists
     */
    void add_vertex(const vertex& v);

    /**
     * Gets a vertex by its name.
     * @param name The name of the vertex
     * @return The vertex with the given name
     */
    vertex get_vertex(const std::string& name) const;

    /**
     * Removes a vertex by its name.
     * @param name The name of the vertex
     * @throws std::invalid_argument if the vertex does not exist
     */
    void remove_vertex(const std::string& name);

    /**
     * Creates or updates an edge between v1 and v2 with the given weight.
     * @param v1 vertex 1
     * @param v2 vertex 2
     * @param weight weight of the edge (default is 0)
     * @return true if the edge was created or updated successfully, false otherwise
     */
    void set_edge(const vertex& v1, const vertex& v2, long weight = 0);

    /**
     * Retrieves the weight of the edge between v1 and v2.
     * @param v1 vertex 1
     * @param v2 vertex 2
     * @return The weight of the edge between v1 and v2
     * @throws std::invalid_argument if there is no edge between v1 and v2
     */
    long get_edge_weight(const vertex& v1, const vertex& v2) const;

    /**
     * Removes the edge between v1 and v2.
     * @param v1 vertex 1
     * @param v2 vertex 2
     * @return return true if the edge was removed successfully, false otherwise
     */
    bool remove_edge(const vertex& v1, const vertex& v2);
};
#endif //GRAPH_HPP