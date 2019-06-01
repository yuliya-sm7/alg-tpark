#include <iostream>
#include <vector>
#include <queue>

class IGraph {
public:
    virtual void AddEdge(int from, int to) = 0;

    virtual int GetSize() const = 0;

    virtual const std::vector<int> & GetNextVertices(int from) const = 0;
};

class Graph : public IGraph {
public:
    explicit Graph(int vertices_count);

    void AddEdge(int from, int to) final;

    int GetSize() const final;

    const std::vector<int> & GetNextVertices(int from) const final;

private:
    std::vector<std::vector<int>> out_edges;
};

int Graph::GetSize() const {
    return out_edges.size();
}

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

const std::vector<int> & Graph::GetNextVertices(int from) const {
    return out_edges[from];
}

void Bfs(const IGraph &graph, int from, std::vector<int> &paths, std::vector<int> &depth) {
    std::queue<int> q;
    q.push(from);
    paths[from] = 1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        const std::vector<int> & next_vertices = graph.GetNextVertices(current);

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

int ShortestPathsCount(const IGraph &graph, int from, int to) {
    std::vector<int> paths(graph.GetSize());
    std::vector<int> depth(graph.GetSize());
    Bfs(graph, from, paths, depth);
    return paths[to];
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
    std::cout << ShortestPathsCount(graph, in, out) << std::endl;
    return 0;
}