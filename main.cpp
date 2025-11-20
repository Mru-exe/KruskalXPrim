#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.hpp"
#include "UnionFind.hpp"
#include "MST.hpp"

/**
 * Reads a graph from a file. The file is expected to contain the adjacency list of the Graph.
 * @return The graph read from the file.
 */
Graph readFromFile(std::string filename) {
    Graph g;
    UnionFind uf;

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::invalid_argument("Could not open file " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        long v1, v2, w;
        if (iss >> v1 >> v2 >> w) {
            g.addEdge(v1, v2, w);
            uf.unite(v1, v2);
        } else {
            std::cerr << "Invalid character sequence on line: " << line << std::endl;
        }
    }
    file.close();

    if (uf.getSetCount() != 1) {
        throw std::invalid_argument("The provided graph is not connected.");
    }
    return g;
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