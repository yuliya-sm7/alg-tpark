
#include <iostream>
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"


void printV(const IGraph& graph, int vert) {

    std::cout << "Колличество вершин: " << graph.VerticesCount() << std::endl;

    std::cout << "Входящие ребра для " << vert;
    std::vector<int> prev_vertices = graph.GetPrevVertices(vert);
    for (int v : prev_vertices) {
        std::cout << " (" << v << "," << vert << ")";
    }
    std::cout << std::endl;

    std::cout << "Выходящие ребра для " << vert;
    vector<int> next_vertices = graph.GetNextVertices(vert);
    for (int v : next_vertices) {
        std::cout << " (" << vert << "," << v << ")";
    }
    std::cout << std::endl;
}


int main() {
    CListGraph graph(4);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(2, 3);
    graph.AddEdge(2, 0);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 1);

    CListGraph list(&graph);
    list.show();
    printV(list, 0);

    CMatrixGraph matrix(&graph);
    matrix.show();
    printV(matrix, 1);

    CSetGraph set(&graph);
    set.show();
    printV(set, 2);

    CArcGraph arc(&graph);
    arc.show();
    printV(arc, 3);

    return 0;
}