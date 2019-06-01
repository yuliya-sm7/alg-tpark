#ifndef INC_1DZ_CSETGRAPH_H
#define INC_1DZ_CSETGRAPH_H

#include "IGraph.h"
#include <unordered_set>


class CSetGraph : public IGraph {
public:
    CSetGraph(unsigned int verticesCount);

    CSetGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    void show();

private:
    unsigned int verticesCount_;
    std::vector<std::unordered_set<int>> out_;
    std::vector<std::unordered_set<int>> in_;
};


#endif //INC_1DZ_CSETGRAPH_H
