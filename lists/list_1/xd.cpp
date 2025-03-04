#include <iostream>
#include <cmath>
using namespace std;

int P(int i, int j) {
    return j;
}

void alg(int n) {
    int sum = 0;

    for (int i = 1; i <= n; i++) {
        int j = i;
        sum++;
        while (j < n) {
            sum++;
            sum++;
            j++;
        }
    }

    cout << "Suma operacji: " << sum << endl;
}

void alg2(int n) {
    int sum = 0;

    for (int i = 1; i <= n; i++) {
        int j = i;
        sum++;
        while (j < n) {
            sum++;
            sum+=j;
            j=j+j;
        }
    }

    cout << "Suma operacji: " << sum << endl;
}

void ile(int n) {
    cout<<"Nasz wzór: "<< (n*n*n + 2*n)/3<<endl;
}

void ile2(int n) {
    int sum = 0;
    for(int i=1; i<=n; i++) {
        sum+=1;
        int xd = ceil(log2((double)n/(double)i)) - 1;
        for(int j=0; j<=xd; j++) {
            sum+=2;
        }
    }
    cout<<sum<<endl;
}

void ile3(int n) {
    cout<<n*n<<'\n';
}

int main() {
   
    for(int i=1; i<=10; i++){
        alg2(i);
        ile2(i);
        ile3(i);
    }

    return 0;
}

