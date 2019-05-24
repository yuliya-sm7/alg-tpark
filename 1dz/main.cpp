
#include <iostream>
#include "CListGraph.h"

void list_graph(const IGraph& graph_input) {

    CListGraph graph(&graph_input);
    graph.Print(std::cout);

    std::cout << "Колличество вершин: " << graph.VerticesCount() << std::endl;
    int  vert = 1;

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

    list_graph(graph);

    return 0;
}