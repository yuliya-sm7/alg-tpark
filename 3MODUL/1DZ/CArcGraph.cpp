#include "CArcGraph.h"

CArcGraph::CArcGraph(unsigned int verticesCount) :
        verticesCount_(verticesCount) {}

CArcGraph::CArcGraph(const IGraph *graph) :
        verticesCount_(graph->VerticesCount()) {
    CopyGraph(graph);
}

void CArcGraph::AddEdge(int from, int to) {
    // провека на наличие ребра в графе
    for (const auto &edge : edges_) {
        if (edge.from == from && edge.to == to) {
            return;
        }
    }

    Edge edge(from, to);
    edges_.push_back(edge);
}

int CArcGraph::VerticesCount() const {
    return verticesCount_;
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (const auto &edge : edges_) {
        if (edge.from == vertex) {
            vertices.push_back(edge.to);
        }
    }
    return vertices;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (const auto &edge : edges_) {
        if (edge.to == vertex) {
            vertices.push_back(edge.from);
        }
    }
    return vertices;
}

void CArcGraph::show() {
    std::cout << std::endl;
    std::cout << "CArcGraph:" << std::endl;
    int prev_from = -1;
    for (auto &e : edges_) {
        if (e.from == prev_from) {
            continue;
        }
        std::cout << e.from << ": ";
        for (auto &ed : edges_) {
            if (e.from == ed.from) {
                std::cout << ed.to << " ";
            }
        }
        prev_from = e.from;
        std::cout << std::endl;
    }
}