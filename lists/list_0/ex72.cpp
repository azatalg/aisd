#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;
static const int LOGN = 17;

vector<int> adj[MAXN + 1];
int parent[MAXN + 1][LOGN + 1];
int depth[MAXN + 1];

void dfs(int v, int p) {
    parent[v][0] = p;
    depth[v] = (v == p ? 0 : depth[p] + 1);
    for (int nxt : adj[v]) {
        if(nxt != p)
            dfs(nxt, v);
    }
}

void buildParent(int n) {
    for(int k = 1; k <= LOGN; k++) {
        for(int v = 1; v <= n; v++) {
            parent[v][k] = parent[ parent[v][k-1] ][k-1];
        }
    }
}

int LCA(int x, int y) {
    if(depth[x] < depth[y]) swap(x, y);
    int diff = depth[x] - depth[y];
    for(int k = 0; k <= LOGN; k++) {
        if(diff & (1 << k)) {
            x = parent[x][k];
        }
    }
    if(x == y) return x;
    for(int k = LOGN; k >= 0; k--) {
        if(parent[x][k] != parent[y][k]) {
            x = parent[x][k];
            y = parent[y][k];
        }
    }
    return parent[x][0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 1);
    buildParent(n);
    while(m--){
        int v, u;
        cin >> v >> u;
        int l = LCA(v, u);
        if(l == v) cout << "TAK\n";
        else cout << "NIE\n";
    }
    return 0;
}

