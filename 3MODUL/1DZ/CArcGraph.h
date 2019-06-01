#ifndef INC_1DZ_CARCGRAPH_H
#define INC_1DZ_CARCGRAPH_H

#include "IGraph.h"

class CArcGraph : public IGraph {
public:
    CArcGraph(unsigned int verticesCount);

    CArcGraph(const IGraph *graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    void show();

private:
    struct Edge{
        Edge(int from, int to) :
                from(from),
                to(to)
        {};
        int from;
        int to;
    };
    unsigned int verticesCount_;
    std::vector<Edge> edges_;
};


#endif //INC_1DZ_CARCGRAPH_H
