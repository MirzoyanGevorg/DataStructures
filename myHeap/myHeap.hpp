#ifndef MYHEAP_HPP
#define MYHEAP_HPP

#include <vector>

template<typename T>
MyHeap<T>::MyHeap(const std::vector<T>& v) : m_data(v) {
    heapify();
}

template<typename T>
MyHeap<T>::MyHeap(std::vector<T>&& v) : m_data(std::move(v)) {
    heapify();
}

template<typename T>
void MyHeap<T>::print() {
    for (int i = 0; i < m_data.size(); ++i) {
        std::cout << m_data[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void MyHeap<T>::move_down(int i)
{
    int l = left(i);
    int r = right(i);
    int max_index = i;
    if (l < m_data.size() && m_data[l] > m_data[i]) {
        max_index = l;
    }
    if (r < m_data.size() && m_data[r] > m_data[max_index]) {
        max_index = r;
    }
    if (max_index != i) {
        std::swap(m_data[i], m_data[max_index]);
        move_down(max_index);
    }
}

template<typename T>
void MyHeap<T>::move_up() {
    int i = m_data.size() - 1;
    while (i > 0 && m_data[i] > m_data[parent(i)]) {
        std::swap(m_data[i], m_data[parent(i)]);
        i = parent(i);
    }
}

template<typename T>
void MyHeap<T>::heapify() {
    for (int i = parent(m_data.size() - 1); i >= 0; --i) {
        move_down(i);
    }
}

template<typename T>
void MyHeap<T>::pop() {
    m_data[0] = m_data[m_data.size() - 1];
    m_data.pop_back();
    move_down(0);
}

template<typename T>
void MyHeap<T>::push(const T& value) {
    m_data.push_back(value);
    move_up();
}

template<typename T>
void MyHeap<T>::push(T&& value) {
    m_data.push_back(std::move(value));
    move_up();
}

template<typename T>
T MyHeap<T>::top() const {
    return m_data[0];
}

#endif // !MYHEAP_HPP

