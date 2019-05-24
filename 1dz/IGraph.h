//
// Created by yu on 24.05.19.
//

#ifndef INC_1DZ_IGRAPH_H
#define INC_1DZ_IGRAPH_H

#include <vector>
using std::vector;

struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

    void CopyGraph(const IGraph* graph) {
        for (int i = 0; i < graph->VerticesCount(); i++) {
            std::vector<int> vertex;
            vertex = graph->GetNextVertices(i);
            for (auto edge : vertex) {
                AddEdge(i, edge);
            }
        }
    };
};



#endif //INC_1DZ_IGRAPH_H
