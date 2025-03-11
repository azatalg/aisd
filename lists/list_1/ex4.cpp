#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k;
    cin >> k;
    
    unordered_map<char, vector<char>> graph;
    unordered_map<char, int> outdeg, indeg;
    
    vector<string> words(k);
    for (int i = 0; i < k; i++) {
        cin >> words[i];
        if (words[i].size() != 2) continue; 
        char u = words[i][0], v = words[i][1];
        graph[u].push_back(v);
        outdeg[u]++;
        indeg[v]++;
    }
    
    for (auto &p : graph) {
        sort(p.second.begin(), p.second.end(), greater<char>());
    }
    
    char start = '\0';
    for (auto &p : graph) {
        char node = p.first;
        if (outdeg[node] - indeg[node] == 1) {
            start = node;
            break;
        }
    }
    if (start == '\0') {
        start = graph.begin()->first;
    }
    
    // Hierholzer 
    vector<char> path;
    stack<char> st;
    st.push(start);
    
    while (!st.empty()) {
        char v = st.top();
        if (!graph[v].empty()) {
            char u = graph[v].back();
            graph[v].pop_back();
            st.push(u);
        } else {
            path.push_back(v);
            st.pop();
        }
    }
    
    reverse(path.begin(), path.end());
    
    string result;
    if (!path.empty()) {
        result.push_back(path[0]);
        for (size_t i = 1; i < path.size(); i++) {
            result.push_back(path[i]);
        }
    }
    
    cout << result << "\n";
    return 0;
}

