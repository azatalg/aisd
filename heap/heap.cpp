#include <iostream>
#include <ctime>
#include "../vector/vector.h"
using namespace std;

template <typename T>
class Heap {
    Vector<T> data;
    int n;
    void heapifyUp(int i) {
        while(i > 0 && data[i] < data[(i-1)/2]) {
            swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }
    void heapifyDown(int i) {
        while(true) {
            int mini = i;
            int left = i*2+1;
            int right = i*2+2;
            
            if(left < n && data[left] < data[mini]) {
                mini = left;
            }

            if(right < n && data[right] < data[mini]) {
                mini = right;
            }

            if(mini == i) 
                break;

            swap(data[i], data[mini]);
            i = mini;
        }
    }

    void build() {
        for(int i = n/2; i>=0; i--) {
            heapifyDown(i);
        }
    }

public: 
    Heap(Vector<T>& data) : data(data), n(data.size()) {
        build();
    }

    Heap() : n(0) {}

    void display() {
        for(int i=1; i<=n; i++) {
            cout<<data[i-1]<<' ';
            if( (i+1 & i) == 0) {
                cout<<'\n';
            }
        }
    }

    int getMin() {
        return data[0];
    }

    void removeMin() {
        data[0] = data[n-1];
        data.pop_back();
        heapifyDown(0);
        n--;
    }

    void insert(const T& val) {
        data.push_back(val);
        heapifyUp(n++);
    }

    ~Heap() {
    }
};

template <typename T>
void heapSort(Vector<T>& arr) {
    Heap<T> heap(arr);
    arr.push_back(999);
    heap.insert(999);
    heap.display();
    cout<<"\n";
    for(int i = 0; i<arr.size(); i++) {
        arr[i] = heap.getMin();
        heap.removeMin();
    }
}

int main() {
    Vector<int> xd;
    for(int i=0; i<32; i++) {
        xd.push_back(rand()%100 + 10);
    }
    heapSort(xd); 
    for(auto i: xd) cout<<i<<' ';
}
