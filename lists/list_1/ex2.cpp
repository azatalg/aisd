#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Struktura reprezentująca element z listy
struct Node {
    int value;      // wartość elementu
    int listIndex;  // numer listy, z której pochodzi element
    int indexInList;// indeks elementu w liście
};

// Komparator dla kolejki priorytetowej (min-heap)
struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.value > b.value;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    vector<vector<int>> lists(k);

    // Wczytywanie k uporządkowanych list
    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;  // liczba elementów w liście i
        lists[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> lists[i][j];
        }
    }

    // Minimalna kolejka (min-heap) dla śledzenia aktualnych elementów z każdej listy
    priority_queue<Node, vector<Node>, Compare> minHeap;
    int currentMax = numeric_limits<int>::min();

    // Inicjalizacja kolejki – wstawiamy pierwszy element z każdej listy
    for (int i = 0; i < k; i++) {
        if (lists[i].empty()) continue; 
        int value = lists[i][0];
        minHeap.push({value, i, 0});
        if (value > currentMax)
            currentMax = value;
    }

    int bestRange = numeric_limits<int>::max();
    int bestLow = 0, bestHigh = 0;

    // Główna pętla – działamy, dopóki mamy reprezentanta z każdej listy
    while (minHeap.size() == k) {
        Node node = minHeap.top();
        minHeap.pop();
        int currentMin = node.value;

        // Aktualizujemy przedział, jeśli znaleźliśmy mniejszy
        if (currentMax - currentMin < bestRange) {
            bestRange = currentMax - currentMin;
            bestLow = currentMin;
            bestHigh = currentMax;
        }

        // Przesuwamy wskaźnik dla listy, z której pochodził minimalny element
        int nextIndex = node.indexInList + 1;
        if (nextIndex < lists[node.listIndex].size()) {
            int nextValue = lists[node.listIndex][nextIndex];
            minHeap.push({nextValue, node.listIndex, nextIndex});
            if (nextValue > currentMax)
                currentMax = nextValue;
        } else {
            break;
        }
    }

    // Wynik: najmniejsze r takie, że istnieje przedział [a, a+r] spełniający warunki
    cout << bestRange << "\n";
    // Opcjonalnie, można wyświetlić sam przedział:
     cout << "Przedział: [" << bestLow << ", " << bestHigh << "]\n";

    return 0;
}

