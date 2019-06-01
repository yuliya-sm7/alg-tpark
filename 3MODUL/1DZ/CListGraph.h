#ifndef INC_1DZ_CLISTGRAPH_H
#define INC_1DZ_CLISTGRAPH_H

#include "IGraph.h"


class CListGraph : public IGraph {
public:
    CListGraph(int vertices_count);

    CListGraph(const IGraph *graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    void show();

private:
    vector<vector<int>> in_edges_;
    vector<vector<int>> out_edges_;
};


#endif //INC_1DZ_CLISTGRAPH_H
