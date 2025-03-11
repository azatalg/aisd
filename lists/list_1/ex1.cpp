#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

class minmaxHeap {
    vector < int > H, L;
    int n = 0;
    int nh = 0, nl = 0;

    int Lchild(int a) {
        return a * 2 + 1;
    }

    int Rchild(int a) {
        return a * 2 + 2;
    }

    int par(int a) {
        return a / 2;
    }

    void heapifyUpMax(int i) {
        while ((par(i) - 1) >= 0 && H[par(i) - 1] < H[i - 1]) {
            swap(H[par(i) - 1], H[i - 1]);
            i >>= 1;
        }
    }

    void heapifyUpMin(int i) {
        while ((par(i) - 1) >= 0 && L[par(i) - 1] > L[i - 1]) {
            swap(L[par(i) - 1], L[i - 1]);
            i >>= 1;
        }
    }
    void push_H(int x) {
        H.push_back(x);
        nh++;
        int partner = (nh + 1) / 2 - 1;
        if (nl > partner) {
            if (H[nh - 1] < L[partner]) {
                swap(H[nh - 1], L[partner]);
                heapifyUpMin(partner + 1);
                return;
            }
        }
        heapifyUpMax(nh);
    }

    void push_L(int x) {
        L.push_back(x);
        nl++;
        int partner = nl - 1;
        if (nh > partner) {
            if (L[nl - 1] > H[partner]) {
                swap(L[nl - 1], H[partner]);
                heapifyUpMax(partner + 1);
                return;
            }
        }
        heapifyUpMin(nl);
    }

    int heapifyDownMin(int i) {
        i--;
        while (true) {
            int mini = i;
            int left = i * 2 + 1;
            int right = i * 2 + 2;

            if (left < nl && L[left] < L[mini]) {
                mini = left;
            }
            if (right < nl && L[right] < L[mini]) {
                mini = right;
            }
            if (mini == i)
                break;
            swap(L[i], L[mini]);
            i = mini;
        }
        return i + 1;
    }

    int heapifyDownMax(int i) {
        i--;
        while (true) {
            int maxi = i;
            int left = i * 2 + 1;
            int right = i * 2 + 2;

            if (left < nh && H[left] > H[maxi]) {
                maxi = left;
            }
            if (right < nh && H[right] > H[maxi]) {
                maxi = right;
            }
            if (maxi == i)
                break;
            swap(H[i], H[maxi]);
            i = maxi;
        }
        return i + 1;
    }

    public:
        minmaxHeap() {}

    void insert(int x) {
        if (!(n & 1)) {
            push_H(x);
        } else {
            push_L(x);
        }
        n++;
    }
    int deleteMin() {
        int res = nl ? L[0] : H[0];
        if (nl == nh) {
            L[0] = L[nl - 1];
            L.pop_back();
            nl--;
        } else {
            L[0] = H[nh - 1];
            H.pop_back();
            nh--;
        }
        int x = heapifyDownMin(1);
        if (L[x - 1] > H[x - 1]) {
            swap(L[x - 1], H[x - 1]);
            heapifyUpMax(x);
        }
        n--;
        return res;
    }
    int deleteMax() {
        int res = nh ? H[0] : L[0];
        if (nh != nl) {
            H[0] = H[nh - 1];
            H.pop_back();
            nh--;
        } else {
            H[0] = L[nl - 1];
            L.pop_back();
            nl--;
        }
        int x = heapifyDownMax(1);
        if (H[x - 1] < L[x - 1]) {
            swap(H[x - 1], L[x - 1]);
            heapifyUpMin(x);
        }
        n--;
        return res;
    }

    void display() {
        int height = (nh > 0) ? (int) log2(nh) + 1 : 0;
        int maxWidth = (1 << height) - 1;
        int levelStart = 0;
        int j = 1;
        for (int level = 0; level < height; level++) {
            int elementsInLevel = 1 << level;
            int spaceBetween = maxWidth / elementsInLevel;
            cout << string(spaceBetween * 3 / 2, ' ');
            for (int i = 0; i < elementsInLevel && levelStart + i < nh; i++) {
                cout << j << ": " << setw(1) << H[levelStart + i] << string(spaceBetween * 3, ' ');
                j++;
            }
            cout << '\n';
            levelStart += elementsInLevel;
        }
        j = 1;
        vector < string > xd;
        levelStart = 0;
        for (int level = 0; level < height; level++) {
            int elementsInLevel = 1 << level;
            int spaceBetween = maxWidth / elementsInLevel;
            string line = string(spaceBetween * 3 / 2, ' ');
            for (int i = 0; i < elementsInLevel && levelStart + i < nl; i++) {
                line += to_string(j) + ": " + to_string(L[levelStart + i]) + string(spaceBetween * 3, ' ');
                j++;
            }
            xd.push_back(line);
            levelStart += elementsInLevel;
        }

        cout << '\n';
        for (int i = xd.size() - 1; i >= 0; i--) {
            cout << xd[i] << '\n';
        }
    }

    bool check() {
        bool flag = true;
        for (int i = 0; i < nh / 2; i++) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < nh && H[i] < H[left]) flag = false;
            if (right < nh && H[i] < H[right]) flag = false;
        }
        for (int i = 0; i < nl / 2; i++) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < nl && L[i] > L[left]) flag = false;
            if (right < nl && L[i] > L[right]) flag = false;
        }
        return flag;
    }
};

bool xdd() {
    minmaxHeap a;
    bool flag = true;
    for (int i = 0; i < 14; i++) {
        a.insert(rand() % 10);
        flag = a.check();
    }
    if (!flag) return false;
    for (int i = 0; i < 10; i++) {
        a.display();
        cout << "\n\n";
        a.deleteMin();
        a.display();
        cout << "\n\n";
        flag = a.check();
        if (!flag) return false;
    }
    return a.check();
}

bool sortTest() {
    minmaxHeap a;
    minmaxHeap b;
    for (int i = 0; i < 10000; i++) {
        int x = (rand() % 899000 + 100);
        a.insert(x);
        b.insert(x);
    }
    vector < int > yy, xx;
    for (int i = 0; i < 10; i++) {
        yy.push_back(b.deleteMin());
        xx.push_back(a.deleteMax());
    }
    cout << '\n';
    bool flag = true;
    for (int i = 1; i < 10; i++) {
        if (xx[i] > xx[i - 1]) flag = false;
        if (yy[i] < yy[i - 1]) flag = false;
    }
    if (!flag) {
        for (auto i: xx) cout << i << ' ';
        cout << '\n';
    }
    return flag;
}

int main() {
    srand(time(NULL));
    int i = 0;
    while (sortTest()) {
        cout << "Ok: " << ++i << '\n';
    }
    return 0;
}
