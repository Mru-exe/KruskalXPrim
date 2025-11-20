#include "Graph.hpp"

#include <chrono>

#include "UnionFind.hpp"
#include <iomanip>
#include <ostream>


unsigned int Graph::getVertexCount() const {
    return this->vertices.size();
}

Graph Graph::getRandomGraph(unsigned int maxId, unsigned long maxWeight) {
    Graph g;
    UnionFind uf;

    srand(std::chrono::system_clock::now().time_since_epoch().count());
    long A,B,W;
    do {
        A = rand() % 100;
        B = rand() % 100;
        W = rand() % 50;
        g.addEdge(A, B, (W+1));
        uf.unite(A, B);
    } while (uf.getSetCount() != 1 || g.getEdgeList().size() < 5);

    return g;
}

void Graph::addEdge(long A, long B, long W) {
    // Add vertices to the set and check if they were new
    auto [iterA, insertedA] = this->vertices.insert(A);
    auto [iterB, insertedB] = this->vertices.insert(B);
    
    // If at least one vertex is new, the edge cannot exist yet
    if (insertedA || insertedB) {
        this->edgeList.push_back({A, B, W});
        return;
    }
    
    // Both vertices existed, check if edge already exists (in either direction)
    for (auto& edge : this->edgeList) {
        if ((edge.a == A && edge.b == B) || (edge.a == B && edge.b == A)) {
            // Update existing edge weight
            edge.weight = W;
            return;
        }
    }
    
    // Add new edge
    this->edgeList.push_back({A, B, W});
}

std::vector<Graph::Edge>& Graph::getEdgeList() const {
    return const_cast<std::vector<Graph::Edge>&>(this->edgeList);
}

void Graph::print(std::ostream& os, bool minimal) const {
    if (minimal) {
        for (auto edge : this->edgeList) {
            os << edge.a << " " << edge.b << " " << edge.weight << std::endl;
        }
    } else {
        os << "U -- V [weight]" << std::endl;
        os << "- - - - - - - -" << std::endl;
        for (auto edge : this->edgeList) {
            os << edge.a << " -- " << edge.b << " [" << edge.weight << "]" << std::endl;
        }
    }
}

bool Graph::Edge::operator==(Edge other) {
    return (a == other.a) && (b == other.b);
}