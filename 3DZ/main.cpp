#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>

const int inf = std::numeric_limits<int>::max() / 2;

class ListGraph {
public:
    explicit ListGraph(int vertices_count);

    void AddEdge(int from, int to, int weight);

    int VerticesCount() const;

    struct Vertice {
        Vertice(int value, int path) : val(value), path_weight(path) {}

        int val;
        int path_weight;

        bool operator<(const Vertice &other) const {
            return ((path_weight < other.path_weight) || (path_weight == other.path_weight && val < other.val));
        }
    };

    std::vector<Vertice> GetNextVertices(int vertex) const;

private:
    std::vector<std::vector<Vertice>> out_edges_;
};


ListGraph::ListGraph(int vertices_count) :
        out_edges_(vertices_count) {}

int ListGraph::VerticesCount() const {
    return out_edges_.size();
}

void ListGraph::AddEdge(int from, int to, int weight) {
    out_edges_[to].emplace_back(Vertice(from, weight));
    out_edges_[from].emplace_back(Vertice(to, weight));
}

std::vector<ListGraph::Vertice> ListGraph::GetNextVertices(int vertex) const {
    return out_edges_[vertex];
}


int BestRoute(const ListGraph &graph, int from, int to) {

    std::vector<int> min_paths(graph.VerticesCount(), inf);
    min_paths[from] = 0;
    std::set<int> set;
    set.emplace(from);

    while (!set.empty()) {
        auto current = *set.begin();
        set.erase(set.begin());

        std::vector<ListGraph::Vertice> vertices = graph.GetNextVertices(current);

        for (auto item : vertices) {
            if (min_paths[item.val] > min_paths[current] + item.path_weight) {
                set.erase(item.val);
                min_paths[item.val] = min_paths[current] + item.path_weight;
                set.emplace(item.val);
            }
        }
    }
    if (min_paths[to] == inf) {
        return -1;
    }
    return min_paths[to];
}


int main() {
    int vertices_count = 0;
    int edge_count = 0;
    std::cin >> vertices_count >> edge_count;
    ListGraph graph(vertices_count);

    int in = 0;
    int out = 0;
    int weight = 0;
    for (int i = 0; i < edge_count; i++) {
        std::cin >> in >> out >> weight;
        graph.AddEdge(in, out, weight);
    }

    std::cin >> in >> out;
    std::cout << BestRoute(graph, in, out) << std::endl;
    return 0;
}