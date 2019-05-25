#include "CSetGraph.h"

CSetGraph::CSetGraph(unsigned int verticesCount) :
        verticesCount_(verticesCount),
        out_(verticesCount_),
        in_(verticesCount_) {}

CSetGraph::CSetGraph(const IGraph *graph) :
        verticesCount_(graph->VerticesCount()),
        out_(verticesCount_),
        in_(verticesCount_) {
    CopyGraph(graph);
}

void CSetGraph::AddEdge(int from, int to) {
    out_[from].insert(to);
    in_[to].insert(from);
}

int CSetGraph::VerticesCount() const {
    return verticesCount_;
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (auto i : out_[vertex]) {
        vertices.push_back(i);
    }
    return vertices;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (auto i : in_[vertex]) {
        vertices.push_back(i);
    }
    return vertices;
}

void CSetGraph::show() {
    std::cout << std::endl;
    std::cout << "CSetGraph:" << std::endl;
    for (int i = 0; i < out_.size(); i++) {
        std::cout << i << ": ";
        for (int out_target : out_[i]) {
            std::cout << out_target << " ";
        }
        std::cout << std::endl;
    }
}