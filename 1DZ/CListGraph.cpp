//
// Created by yu on 24.05.19.
//

#include "CListGraph.h"


CListGraph::CListGraph(int vertices_count) :
        in_edges_(vertices_count),
        out_edges_(vertices_count)
{}

CListGraph::CListGraph(const IGraph* graph) :
        in_edges_(graph->VerticesCount()),
        out_edges_(graph->VerticesCount())
{
    CopyGraph(graph);
}

int CListGraph::VerticesCount() const {
    return out_edges_.size();
}

void CListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < VerticesCount());
    assert(to >= 0 && to < VerticesCount());

    // проверка наличия ребра в графе
    for (auto edge : in_edges_[to]) {
        if (edge == from) {
            return;
        }
    }
    for (auto edge : out_edges_[from]) {
        if (edge == to) {
            return;
        }
    }

    in_edges_[to].push_back(from);
    out_edges_[from].push_back(to);
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < VerticesCount());
    return out_edges_[vertex];
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < VerticesCount());
    return in_edges_[vertex];
}

void CListGraph::show() {
    std::cout << std::endl;
    std::cout << "CListGraph:" << std::endl;
    for (int i = 0; i < out_edges_.size(); i++) {
        std::cout << i << ": ";
        for (auto out_target : out_edges_[i]) {
            std::cout << out_target << " ";
        }
        std::cout << std::endl;
    }
}
