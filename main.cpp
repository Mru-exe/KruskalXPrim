#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Graph.hpp"
#include "UnionFind.hpp"
#include "MST.hpp"

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

/**
 * Reads a graph from a file. The file is expected to contain the adjacency list of the Graph.
 * @return The graph read from the file.
 */
Graph readFromFile(const std::string& filename) {
    Graph g;
    UnionFind uf;

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::invalid_argument("Could not open file " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (long v1, v2, w; iss >> v1 >> v2 >> w) {
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

enum RunOption {
    HELP,
    GENERATE,
    KRUSKAL_ONLY,
    PRIM_ONLY,
    BOTH,
    FAIL
};

struct RunArgs {
    bool useFormatting = false;
    std::string filename;
    int generatorAmplifier = 20;
};

/**
 * Parses command line arguments and returns a pair of RunOption and RunArgs.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return A pair of RunOption and RunArgs.
 */
std::pair<RunOption, RunArgs> parseArguments(const int& argc, char* argv[]) {
    std::set<std::string> flagSet;
    for (int i = 1; i < argc; ++i) {
        flagSet.insert(argv[i]);
    }

    RunOption opt = BOTH;
    RunArgs flg = {};
    auto out = std::make_pair(opt, flg);

    out.second.useFormatting = (flagSet.contains("-f") || flagSet.contains("--formatted"));

    if (argc < 2) {
        out.first = FAIL;
        return out;
    }

    if (flagSet.contains("--help")) {
        out.first = HELP;
        return out;
    }

    if (flagSet.contains("-g") || flagSet.contains("--generate")) {
        out.first = GENERATE;
        int amp = std::atoi(argv[argc-1]);
        out.second.generatorAmplifier = (amp > 5) ? amp : out.second.generatorAmplifier;
        return out;
    }

    if (flagSet.contains("-k") || flagSet.contains("--kruskal")) {
        out.first = KRUSKAL_ONLY;
    }
    if (flagSet.contains("-p") || flagSet.contains("--prim")) {
        if (out.first == KRUSKAL_ONLY) {
            out.first = BOTH;
        } else {
            out.first = PRIM_ONLY;
        }
    }
    if (argv[argc-1][0] != '-') {
        out.second.filename = argv[argc-1];
    } else {
        out.first = FAIL;
    }
    return out;
}

int main(int argc, char* argv[]) {
    auto args = parseArguments(argc, argv);
    RunOption runOption = args.first;

    switch (runOption) {
        case(HELP): {
            std::cout << "# Kruskal's and Prim's MST Algorithm comparison" << std::endl;
            std::cout << "* Usage: ./kxp [options] <filename>" << std::endl << std::endl;

            std::cout << "# OPTIONS:" << std::endl;
            std::cout << "*  --help                      Display this help message." << std::endl;
            std::cout << "*  -g, --generate [amplifier]  Generate a random, connected graph. Amplifier is optional, default is 20 and values less than 5 are ignored." << std::endl;
            std::cout << "*  -k, --kruskal               Compute only Kruskal's MST from the input file." << std::endl;
            std::cout << "*  -p, --prim                  Compute only Prim's MST from the input file." << std::endl;
            std::cout << "*  -f, --formatted             Use formatted output for the graphs." << std::endl;
            std::cout << "*  [no arguments]              Compute both Kruskal's and Prim's MST from the input file." << std::endl;
            std::cout << "*  <filename>                  The input file containing the graph's edge list." << std::endl << std::endl;

            std::cout << "# FILE FORMAT:" << std::endl;
            std::cout << "*  The input file should contain the edge list of a CONNECTED graph." << std::endl;
            std::cout << "*  Each line representing an edge in the format: <vertex1> <vertex2> <weight>" << std::endl;
            return 0;
        }
        case(GENERATE): {
            Graph random = Graph::getRandomGraph(args.second.generatorAmplifier, args.second.generatorAmplifier/2);
            random.print(std::cout, !args.second.useFormatting);
            return 0;
        }
        case(BOTH): {
            Graph input;
            try {
                input = readFromFile(args.second.filename);
            }
            catch (std::invalid_argument& e) {
                std::cerr << "* " << e.what() << std::endl;
                return 1;
            }
            auto startK = std::chrono::high_resolution_clock::now();
            Graph kruskalMST = MST::kruskal(input);
            auto endK = std::chrono::high_resolution_clock::now();
            auto startP = std::chrono::high_resolution_clock::now();
            Graph primMST = MST::prim(input);
            auto endP = std::chrono::high_resolution_clock::now();


            std::cout << "* Kruskals' MST (" << to_ms(endK - startK).count() << "ms):" << std::endl;
            kruskalMST.print(std::cout, !args.second.useFormatting);
            std::cout << std::endl;
            std::cout << "* Prims' MST (" << to_ms(endP - startP).count() << "ms):" << std::endl;
            primMST.print(std::cout, !args.second.useFormatting);
            return 0;
        }
        case(PRIM_ONLY): {
            Graph input;
            try {
                input = readFromFile(args.second.filename);
            }
            catch (std::invalid_argument& e) {
                std::cerr << "* " << e.what() << std::endl;
                return 1;
            }
            auto startP = std::chrono::high_resolution_clock::now();
            Graph primMST = MST::prim(input);
            auto endP = std::chrono::high_resolution_clock::now();

            std::cout << "* Prims' MST (" << to_ms(endP - startP).count() << "ms):" << std::endl;
            primMST.print(std::cout, !args.second.useFormatting);
            return 0;
        }
        case(KRUSKAL_ONLY): {
            Graph input;
            try {
                input = readFromFile(args.second.filename);
            }
            catch (std::invalid_argument& e) {
                std::cerr << "* " << e.what() << std::endl;
                return 1;
            }
            auto startK = std::chrono::high_resolution_clock::now();
            Graph kruskalMST = MST::kruskal(input);
            auto endK = std::chrono::high_resolution_clock::now();

            std::cout << "* Kruskals' MST (" << to_ms(endK - startK).count() << "ms):" << std::endl;
            kruskalMST.print(std::cout, !args.second.useFormatting);
            return 0;
        }
    default:
        case(FAIL): {
            std::cerr << "* Invalid arguments." << std::endl;
            std::cerr << "* Try running: ./kxp --help, to display help." << std::endl;
            return 1;
        }
    }
}