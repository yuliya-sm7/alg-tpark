//
// Created by yu on 24.05.19.
//

#ifndef INC_1DZ_CLISTGRAPH_H
#define INC_1DZ_CLISTGRAPH_H

#include "IGraph.h"
#include <cassert>
#include <iostream>

class CListGraph : public IGraph {
public:
    CListGraph(int vertices_count);
    CListGraph(const IGraph* graph);


    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

    void Print(std::ostream& out);
private:
    vector<vector<int>> in_edges_;
    vector<vector<int>> out_edges_;
    //int vertices_count_;
};


#endif //INC_1DZ_CLISTGRAPH_H
