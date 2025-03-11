#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Wprowadź liczbę wierzchołków i krawędzi
    int n, m;
    cin >> n >> m;

    // Graf reprezentowany jako lista sąsiedztwa, oraz tablica na stopnie wejściowe
    vector<vector<int>> graph(n + 1);
    vector<int> in_degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        in_degree[v]++;
    }

    // Kopiec minimalny: wybieramy zawsze najmniejszy element
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> top_order;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        top_order.push_back(u);

        for (int v : graph[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                pq.push(v);
            }
        }
    }

        for (int v : top_order) {
            cout << v << " ";
        }
        cout << "\n";

    return 0;
}

