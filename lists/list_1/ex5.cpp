#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m; // Liczba wierzchołków i krawędzi
    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);
    
    // Wczytywanie grafu (zakładamy numerację od 0 do n-1)
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }
    
    // Topologiczne sortowanie przy użyciu algorytmu Kahna
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }
    
    vector<int> topOrder;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topOrder.push_back(u);
        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
    }
    
    // Tablice dp oraz pred do przechowywania długości drogi i poprzedników
    vector<int> dp(n, 0);
    vector<int> pred(n, -1);
    
    // Droga zgodnie z kolejnością topologiczną
    for (int u : topOrder) {
        for (int v : graph[u]) {
            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                pred[v] = u;
            }
        }
    }
    
    // Szukanie wierzchołka końcowego najdłuższej drogi
    int max_length = 0;
    int end_vertex = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_length) {
            max_length = dp[i];
            end_vertex = i;
        }
    }
    
    cout << "Długość najdłuższej drogi: " << max_length << "\n";
    
    // Rekonstrukcja najdłuższej drogi
    vector<int> path;
    int cur = end_vertex;
    while (cur != -1) {
        path.push_back(cur);
        cur = pred[cur];
    }
    reverse(path.begin(), path.end());
    
    cout << "Najdłuższa droga: ";
    for (int v : path)
        cout << v << " ";
    cout << "\n";
    
    return 0;
}

