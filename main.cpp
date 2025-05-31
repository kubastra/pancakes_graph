#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "graph.h"

// Pomocnicza funkcja – tworzy macierz sąsiedztwa
std::vector<std::vector<int>> getAdjacencyMatrix(const AdjacencyGraph& graph, int size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            matrix[i][j] = graph.getEdgeValue(i, j);
        }
    }
    return matrix;
}

// Sortowanie topologiczne (algorytm Kahna)
void topologicalSort(const AdjacencyGraph& graph, const std::map<int, std::string>& taskNames) {
    int n = taskNames.size();
    std::vector<int> inDegree(n, 0);
    std::vector<std::vector<int>> adj = getAdjacencyMatrix(graph, n);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (adj[i][j] == 1) inDegree[j]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i){
        if (inDegree[i] == 0) q.push(i);
    }

    std::cout << "Kolejnosc wykonywania czynnosci:\n";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        std::cout << "- " << taskNames.at(u) << std::endl;

        for (int v = 0; v < n; ++v){
            if (adj[u][v] == 1) {
                inDegree[v]--;
                if (inDegree[v] == 0) q.push(v);
            }
        }
    }
}

int main() {
    std::map<int, std::string> taskNames = {
        {0, "Nagrzac patelnie"},
        {1, "Zmieszac jajko, olej, mleko i proszek do naleśnikow"},
        {2, "Wylac ciasto nalesnikowe na patelnie"},
        {3, "Przewrocic nalesnik i podpiec z drugiej strony"},
        {4, "Podgrzac syrop klonowy"},
        {5, "Zjesc nalesnik polany syropem"}
    };

    AdjacencyGraph g;

    for (int i = 0; i < 6; ++i) {
        g.addVertex(i);
    }

    g.addEdge(0, 2); // nagrzać patelnię -> wylać ciasto
    g.addEdge(1, 2); // zmieszać składniki -> wylać ciasto
    g.addEdge(2, 3); // wylać ciasto -> przewrócić
    g.addEdge(3, 5); // przewrócić -> zjeść
    g.addEdge(4, 5); // podgrzać syrop -> zjeść

    topologicalSort(g, taskNames);

    return 0;
}
