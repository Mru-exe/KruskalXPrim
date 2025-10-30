#include <cstring>
#include <iostream>
#include "Graph.hpp"

/**
 * Reads a graph from a file. The file is expected to contain the adjacency list of the Graph.
 * @return The graph read from the file.
 */
Graph readFromFile() {
    Graph g;
    //TODO: Implement file reading logic
    return g;
}

/**
 * Performs Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a given graph.
 * @param g The input graph.
 * @return Sub-graph of g representing the MST.
 */
Graph kruskal(const Graph g) {
    Graph mst;
    //TODO: Implement Kruskal's algorithm
    return mst;
}

/**
 * Performs Prim's algorithm to find the Minimum Spanning Tree (MST) of a given graph.
 * @param g The input graph.
 * @return Sub-graph of g representing the MST.
 */
Graph prim(const Graph g) {
    Graph mst;
    //TODO: Implement Prim's algorithm
    return mst;
}

int main(int argc, char** argv) {
    if (argc == 2) {
        if (strcmp(argv[1], "--help")==0) {
            std::cout << std::endl;
            std::cout << "# ABOUT:" << std::endl;
            std::cout << "# \t This program will compute the Minimum Spanning Tree (MST) using both Kruskal's and Prim's algorithms." << std::endl;
            std::cout << "# \t The input graph is expected to be undirected and with weighted edges." << std::endl;
            std::cout << "# \t The edge weight 0 is allowed and considered a valid edge" << std::endl;

            std::cout << "# HOW TO USE:" << std::endl;
            std::cout << "# \t Usage: " << argv[0] << " <input_file>" << std::endl;
            std::cout << "# \t - To calculate MSTs from graph provided in <input_file>" << std::endl;
            std::cout << "#" << std::endl;
            std::cout << "# \t Or use " << argv[0] << " --help" << std::endl;
            std::cout << "# \t - to display this message." << std::endl;
        } else {
            //TODO: Read graph from file and run both algorithms.
            //TODO: Print the resulting MSTs and their total weights.
        }
    } else {
        std::cerr << "Invalid argument(s)." << std::endl;
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        std::cerr << "Use --help to display a manual" << std::endl;
        return 1;
    }
    return 0;
}