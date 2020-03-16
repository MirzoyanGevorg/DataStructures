#ifndef MYHEAP_H
#define MYHEAP_H

#include <vector>

template<typename T>
class MyHeap {
    std::vector<T> m_data;

private:
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void move_down(int i);
    void move_up();
    void heapify();

public:
    MyHeap() = default;
    MyHeap(const std::vector<T>& v);
    MyHeap(std::vector<T>&& v);

    void print();
    void pop();
    void push(const T& value);
    void push(T&& value);
    T top() const;
};

#include "myHeap.hpp"
#endif // !MYHEAP_H

