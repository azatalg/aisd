#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class Vector {
    T* data;
    int n;
    int capacity;
    
public:
    Vector() : capacity(20), n(0) {
        data = new T[capacity];
    }

    Vector(int initSize) : capacity(initSize), n(initSize) {
        data = new T[capacity];
    }

    Vector(int initSize, const T& val) : capacity(initSize), n(initSize) {
        data = new T[capacity];
        for(int i=0; i<n; i++) {
            data[i] = val;
        }
    }

    Vector(initializer_list<T> initList) : capacity(initList.size()), n(initList.size()) {
        data = new T[capacity];
        int i = 0;
        for(auto& elem: initList) 
            data[i++] = elem;
    }

    Vector(const Vector& other) : capacity(other.capacity), n(other.n) {
        data = new T[capacity];
        for(int i=0; i<n; i++) {
            data[i] = other.data[i];
        }
    }

    Vector(Vector&& other) : data(other.data), capacity(other.capacity), n(other.n) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    Vector& operator=(const Vector& other) {
        if(this == &other) {
            return *this;
        }
        delete [] data;
        capacity = other.capacity;
        n = other.n;
        data = new T[capacity];
        for(int i=0; i<n; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Vector& operator=(Vector&& other) {
        if(this == &other) {
            return *this;
        }
        delete[] data;
        data = other.data;
        capacity = other.capacity;
        n = other.n;
        other.data = nullptr;
        other.capacity = 0;
        other.n = 0;
        return *this;
    }
    
    ~Vector() {
        delete [] data;
    }
    
    void resize() {
        capacity <<= 1;
        T* newData = new T[capacity];
        for(int i=0; i<n; i++) {
            newData[i] = data[i];
        }
        delete [] data;
        data = newData;
    }

    void push_back(const T& value) {
        if(n == capacity) resize();
        data[n++] = value;
    }

    void pop_back() {
        if(n > 0) n--;
    }

    T& operator[](int i) {
        return data[i];
    }

    const T& operator[](int i) const {
        return data[i];
    }

    const int size() const {
        return n;
    } 

    bool empty() const {
        return n == 0;
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data+n;
    }
};
