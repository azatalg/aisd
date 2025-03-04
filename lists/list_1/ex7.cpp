#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 1e6;
int p[SIZE];

bool check(int u, int v) {
    while(u != 1) {
        if(u == v) 
            return true;
        u = p[u];
    }
    return false;
}

int main() {
    int n; cin>>n; 
    for(int i=0;i<n-1; i++) {
        int a, b; cin>>a>>b;
        p[b] = a;
    }
}
