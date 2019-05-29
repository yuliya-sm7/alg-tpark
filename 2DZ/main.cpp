#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    explicit Graph(int vertices_count);

    void AddEdge(int from, int to);

    int ShortestPathsCount(int from, int to);

private:

    std::vector<std::vector<int>> out_edges;

    void Bfs(int from, std::vector<int> &paths, std::vector<int> &depth);
};


Graph::Graph(int vertices_count) :
        out_edges(vertices_count) {}


void Graph::AddEdge(int from, int to) {
    // проверка наличия ребра в графе
    for (auto edge : out_edges[from]) {
        if (edge == to) {
            return;
        }
    }
    out_edges[to].push_back(from);
    out_edges[from].push_back(to);
}

int Graph::ShortestPathsCount(int from, int to) {
    std::vector<int> paths(out_edges.size());
    std::vector<int> depth(out_edges.size());
    Bfs(from, paths, depth);
    return paths[to];
}

void Graph::Bfs(int from, std::vector<int> &paths, std::vector<int> &depth) {
    std::queue<int> q;
    q.push(from);
    paths[from] = 1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        std::vector<int> next_vertices = out_edges[current];

        for (auto item : next_vertices) {
            // если не была посещена, добавляем в очередь
            if (paths[item] == 0) {
                q.push(item);
                paths[item] = paths[current];
                depth[item] = depth[current] + 1;
            }
                // если была посещена, и имеет такую же глубину, складываем кол-во путей
            else if (depth[item] == depth[current] + 1) {
                paths[item] += paths[current];
            }
        }
    }
}


int main() {
    int vertices_count = 0;
    int edge_count = 0;
    std::cin >> vertices_count >> edge_count;
    Graph graph(vertices_count);

    int in = 0;
    int out = 0;
    for (int i = 0; i < edge_count; i++) {
        std::cin >> in >> out;
        graph.AddEdge(in, out);
    }

    std::cin >> in >> out;
    std::cout << graph.ShortestPathsCount(in, out) << std::endl;
    return 0;
}