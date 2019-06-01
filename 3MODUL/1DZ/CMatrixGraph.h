#ifndef INC_1DZ_CMATRIXGRAPH_H
#define INC_1DZ_CMATRIXGRAPH_H

#include "IGraph.h"


class CMatrixGraph : public IGraph {
public:
    CMatrixGraph(unsigned int verticesCount);

    CMatrixGraph(const IGraph *graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    void show();

private:
    unsigned int verticesCount_;
    std::vector<std::vector<bool>> edges_;
};


#endif //INC_1DZ_CMATRIXGRAPH_H
