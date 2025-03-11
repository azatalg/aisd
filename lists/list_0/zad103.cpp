#include <bits/stdc++.h>
using namespace std;
const int SIZE = 1e6;
typedef long long ll;
vector<pair<int, int>> adj[SIZE];
ll distancee[SIZE];
int backTrack[SIZE];
bool visited[SIZE];
int t;

void dijkstra(int a) {
    // Używamy standardowej kolejki priorytetowej z min-heapiem symulowanym przez max-heap z ujemnymi wartościami.
    priority_queue<pair<ll, int>> q;
    distancee[a] = 0;
    q.push({0, a});
    while(!q.empty()) {
        int cur = q.top().second;
        ll val = -q.top().first;
        q.pop();
        if(visited[cur])
            continue;
        visited[cur] = true; // Finalizujemy wierzchołek cur
        for(auto i : adj[cur]) {
            int v = i.second;
            ll cost = i.first;
            if(distancee[v] > val + cost) {
                distancee[v] = val + cost;
                backTrack[v] = cur;
                q.push({-distancee[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, s;
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        adj[a].push_back({x, b});
    }
    for(int i = 0; i <= n; i++) {
        distancee[i] = 1e18;
        visited[i] = false;
    }
    dijkstra(s);
    if(distancee[t] == 1e18)
        distancee[t] = -1;
    cout << distancee[t] << "\n";
    
    // Jeśli chcesz wypisać całą ścieżkę, możesz dodać poniższy fragment:
    if(distancee[t] != -1) {
        vector<int> path;
        for(int cur = t; cur != s; cur = backTrack[cur])
            path.push_back(cur);
        path.push_back(s);
        reverse(path.begin(), path.end());
        cout << path.size() << "\n";
        for(auto v : path)
            cout << v << " ";
        cout << "\n";
    }
    
    return 0;
}

