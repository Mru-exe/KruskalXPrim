#include "Graph.hpp"
#include <ostream>
#include <random>


unsigned int Graph::getVertexCount() const {
    return this->vertices.size();
}

Graph Graph::getRandomGraph(unsigned int maxId, unsigned long maxWeight) {
    Graph g;
    if (maxId == 0) return g;

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<unsigned long> weightDist(0, maxWeight > 0 ? maxWeight - 1 : 0);

    std::vector<unsigned int> nodes(maxId);
    for (unsigned int i = 0; i < maxId; ++i) {
        nodes[i] = i;
    }

    std::shuffle(nodes.begin(), nodes.end(), rng);

    for (unsigned int i = 1; i < maxId; ++i) {
        std::uniform_int_distribution<unsigned int> targetDist(0, i - 1);
        unsigned int target = nodes[targetDist(rng)];

        g.addEdge(nodes[i], target, weightDist(rng) + 1);
    }

    unsigned long currentEdgeCount = (maxId > 0) ? maxId - 1 : 0;
    std::uniform_int_distribution<unsigned int> nodeDist(0, maxId - 1);

    while (currentEdgeCount < 5) {
        unsigned int A = nodeDist(rng);
        unsigned int B = nodeDist(rng);

        if (A == B && maxId > 1) continue;

        g.addEdge(A, B, weightDist(rng) + 1);
        currentEdgeCount++;
    }

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

const std::set<Graph::Edge>& Graph::getEdges() const {
    return this->edgeList;
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

bool Graph::Edge::operator==(Edge other) const {
    return (a == other.a) && (b == other.b);
}