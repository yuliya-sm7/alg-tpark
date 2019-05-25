//
// Created by yu on 25.05.19.
//

#include "CMatrixGraph.h"

CMatrixGraph::CMatrixGraph(unsigned int verticesCount) :
        verticesCount_(verticesCount),
        edges_(verticesCount_) {
    for (std::vector<bool> &edge : edges_) {
        edge.assign(verticesCount_, false);
    }
}

CMatrixGraph::CMatrixGraph(const IGraph *graph) :
        verticesCount_(graph->VerticesCount()),
        edges_(verticesCount_) {
    for (std::vector<bool> &edge : edges_) {
        //edge = std::vector<bool>(verticesCount_, false);
        edge.assign(verticesCount_, false);
    }
    CopyGraph(graph);
}

void CMatrixGraph::AddEdge(int from, int to) {
    edges_[from][to] = true;
}

int CMatrixGraph::VerticesCount() const {
    return verticesCount_;
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i = 0; i < verticesCount_; i++) {
        if (edges_[vertex][i]) {
            vertices.push_back(i);
        }
    }
    return vertices;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i = 0; i < verticesCount_; i++) {
        if (edges_[i][vertex]) {
            vertices.push_back(i);
        }
    }
    return vertices;
}

void CMatrixGraph::show() {
    std::cout << std::endl;
    std::cout << "CMatrixGraph:" << std::endl;
    for (int i = 0; i < edges_.size(); i++) {
        std::cout << i << ": ";
        for (auto out_target : edges_[i]) {
            std::cout << out_target << " ";
        }
        std::cout << std::endl;
    }
}
