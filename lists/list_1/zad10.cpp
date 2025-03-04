#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
vector<pair<int, ll>> adj[1000000];
ll distt[1000000];
int backTrack[1000000];
int n, m, s, t;
vector<ll> weightt;
void dijkstra(int start) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    distt[start] = weightt[start];
    pq.push({distt[start], start});
    while(!pq.empty()){
        auto [currDist, u] = pq.top();
        pq.pop();
        if(currDist > distt[u]) continue;
        for(auto &edge : adj[u]){
            int v = edge.first;
            ll cost = edge.second;
            if(distt[u] + cost < distt[v]){
                distt[v] = distt[u] + cost;
                backTrack[v] = u;
                pq.push({distt[v], v});
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    weightt.resize(n+1);
    for (int i = 1; i <= n; i++){
        cin >> weightt[i];
    }
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, weightt[b]});
        adj[b].push_back({a, weightt[a]});
    }
    for (int i = 1; i <= n; i++){
        distt[i] = INF;
        backTrack[i] = -1;
    }
    dijkstra(s);
    if(distt[t] == INF){
        cout << -1 << "\n";
    } else {
        vector<int> path;
        for(int cur = t; cur != -1; cur = backTrack[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        cout << distt[t] << " " << path.size() << "\n";
        for(auto v : path)
            cout << v << " ";
        cout << "\n";
    }
    return 0;
}

