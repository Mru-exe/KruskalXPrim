#include "Graph.hpp"
#include <ostream>
#include <random>
#include <algorithm> // for std::shuffle (windows fix)
#include <iostream>

unsigned int Graph::getVertexCount() const {
    return this->vertices.size();
}

Graph Graph::getRandomGraph(unsigned int edges, unsigned long maxWeight) {
    Graph g;
    if (edges == 0) return g;

    unsigned int minimumVertices = static_cast<unsigned int>(
        std::ceil((1 + std::sqrt(1 + 8.0 * edges)) / 2.0)
    );
    unsigned int maximumVertices = edges + 1;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<unsigned int> viableVertexCountDist(minimumVertices, maximumVertices);
    unsigned int vertices = viableVertexCountDist(gen);

    std::uniform_int_distribution<long> weightDist(0, static_cast<long>(maxWeight - 1));
    std::uniform_int_distribution<unsigned int> viableDist(0, vertices);

    for (unsigned int i = 1; i < vertices; ++i) {
        long weight = weightDist(gen);
        unsigned int connectTo = viableDist(gen) % i;
        g.addEdge(i, connectTo, weight);
    }

    unsigned int currentEdges = g.getEdges().size();
    while (currentEdges < edges) {
        long weight = weightDist(gen);
        unsigned int A = viableDist(gen);
        unsigned int B = viableDist(gen);
        if (A != B && !g.hasEdge(A, B)) {
            g.addEdge(A, B, weight);
            currentEdges = g.getEdges().size();
        }
    }

    return g;
}

void Graph::addEdge(long A, long B, long W) {
    this->vertices.insert(A);
    this->vertices.insert(B);
    if (this->hasEdge(A, B)) {
        return; // Edge already exists, do nothing
    }
    this->edges.insert({A, B, W});
}

const std::set<Graph::Edge>& Graph::getEdges() const {
    return this->edges;
}

void Graph::print(std::ostream& os, bool minimal) const {
    if (minimal) {
        for (auto edge : this->edges) {
            os << edge.a << " " << edge.b << " " << edge.weight << std::endl;
        }
    } else {
        os << "U -- V [weight]" << std::endl;
        os << "- - - - - - - -" << std::endl;
        for (auto edge : this->edges) {
            os << edge.a << " -- " << edge.b << " [" << edge.weight << "]" << std::endl;
        }
    }
}

bool Graph::hasEdge(long A, long B) const {
    return (this->edges.contains({A, B, 0})) ||
           (this->edges.contains({B, A, 0}));
}

bool Graph::Edge::operator==(Edge other) const {
    return (a == other.a) && (b == other.b);
}

bool Graph::Edge::operator<(const Edge& other) const {
    if (weight != other.weight) return weight < other.weight;
    if (a != other.a) return a < other.a;
    return b < other.b;
}
