#include "Graph.hpp"

#include <iomanip>
#include <ostream>


unsigned int Graph::getVertexCount() const {
    return this->vertices.size();
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
