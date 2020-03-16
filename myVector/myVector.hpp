#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <memory>
#include "constants.h"

//	Constructor, Destructor, Asignment

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector() noexcept {

}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(const Allocator& alloc) noexcept
	: m_size{ 0 }
	, m_allocator{ alloc } 
{
	m_allocate(constants::default_size);
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(size_t count, const Allocator& alloc)
	: m_size{ 0 }
	, m_allocator{ alloc } 
{
	m_allocate(count);
	while (m_size < count) {
		m_construct(m_size);
		++m_size;
	}
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(size_t count,const T& value, const Allocator& alloc)
	: m_size{ 0 }
	, m_allocator{ alloc } 
{
	m_allocate(count);
	while (m_size < count) {
		m_construct(m_size, value);
		++m_size;
	}
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(const MyVector& other)
	: MyVector(other, other.m_allocator) 
{

}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(const MyVector& other, const Allocator& alloc)
	: m_size{ 0 }
	, m_allocator{ alloc } 
{
	m_allocate(other.m_capacity);
	while (m_size < other.m_size) {
		m_construct(m_size, other[m_size]);
		++m_size;
	}
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(MyVector&& other) noexcept {
	swap(other);
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(const MyVector&& other, const Allocator& alloc) {
	swap(other);
	m_allocator{ alloc };
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::MyVector(std::initializer_list<T> init, const Allocator& alloc)
	: m_size{ 0 },
	m_allocator{ alloc}
{
	size_t count{ init.size() };
	m_allocate(count);
	for (auto val : init) {
		m_construct(m_size, val);
		++m_size;
	}
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>::~MyVector() {
	clear();
	m_allocator.deallocate(m_data, m_capacity);
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>& MyVector<T, Allocator>::operator=(const MyVector& other) {
	swap(MyVector{ other });
	return *this;
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>& MyVector<T, Allocator>::operator=(MyVector&& other) noexcept {
	swap(other);
	return *this;
}

template<typename T, class Allocator>
inline MyVector<T, Allocator>& MyVector<T, Allocator>::operator=(std::initializer_list<T> init) {
	swap(MyVector{ init });
	return *this;
}

//	Element access

template<typename T, class Allocator>
inline T& MyVector<T, Allocator>::operator[](size_t pos) {
	return m_data[pos];
}

template<typename T, class Allocator>
inline const T& MyVector<T, Allocator>::operator[](size_t pos) const {
	return m_data[pos];
}

template<typename T, class Allocator>
inline T& MyVector<T, Allocator>::front() {
	return m_data[0];
}

template<typename T, class Allocator>
inline const T& MyVector<T, Allocator>::front() const {
	return m_data[0];
}

template<typename T, class Allocator>
inline T& MyVector<T, Allocator>::back() {
	return m_data[m_size - 1];
}

template<typename T, class Allocator>
inline const T& MyVector<T, Allocator>::back() const {
	return m_data[m_size - 1];
}

template<typename T, class Allocator>
inline T* MyVector<T, Allocator>::data() noexcept {
	return m_data;
}

template<typename T, class Allocator>
inline const T* MyVector<T, Allocator>::data() const noexcept {
	return m_data;
}

//	Iterators

template<typename T, class Allocator>
inline T* MyVector<T, Allocator>::begin() noexcept {
	return m_data;
}

template<typename T, class Allocator>
inline const T* MyVector<T, Allocator>::begin() const noexcept {
	return m_data;
}

template<typename T, class Allocator>
inline T* MyVector<T, Allocator>::end() noexcept {
	return m_data + m_size;
}

template<typename T, class Allocator>
inline const T* MyVector<T, Allocator>::end() const noexcept {
	return m_data + m_size;
}

//	Capacity

template<typename T, class Allocator>
inline bool MyVector<T, Allocator>::empty() const noexcept {
	return m_size == 0;
}

template<typename T, class Allocator>
inline size_t MyVector<T, Allocator>::size() const noexcept {
	return m_size;
}

template<typename T, class Allocator>
inline size_t MyVector<T, Allocator>::capacity() const noexcept {
	return m_capacity;
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::reserve(size_t new_cap) {
	if (m_capacity < new_cap) {
		m_reallocate(new_cap);
	}
}

//	Modifiers

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::clear() noexcept {
	while (0 < m_size) {
		m_data[--m_size].~T();
	}
}

template<typename T, class Allocator>
inline T* MyVector<T, Allocator>::insert(const T* pos, const T& val) {
	T* iter{ &m_data[pos - m_data] };
	if (m_size = m_capacity) {
		m_reallocate(m_capacity + m_capacity / 2 + 1);
	}
	memmove(static_cast<void*>(iter), static_cast<void*>(iter + 1), (m_size - (iter - m_data)) * sizeof(T));
	++m_size;
	m_construct(iter, val);
	return iter;
}

template<typename T, class Allocator>
inline T* MyVector<T, Allocator>::erase(const T* pos) {
	T* iter{ &m_data[pos - m_data] };
	iter->~T();
	memmove(static_cast<void*>(iter), static_cast<void*>(iter + 1), (m_size - (iter - m_data)) * sizeof(T));
	--m_size;
	return iter;
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::push_back(const T& val) {
	if (m_size == m_capacity) {
		m_reallocate(m_capacity + m_capacity / 2 + 1);
	}
	m_construct(m_size, val);
	return m_data[m_size++];
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::pop_back() {
	m_data[--m_size].~T();
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::resize(size_t count) {
	if (m_size  < count) {
		if (m_capacity < count) {
			m_reallocate(count);
		}
	}
	else {
		while (count < m_size) {
			m_data[--m_size].T();
		}
	}
	m_size{ count };
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::resize(size_t count, const T& val) {
	if (m_size < count) {
		if (m_capacity < count) {
			m_reallocate(count);
		}
		for (size_t i{ m_size }; i < count; ++i) {
			m_construct(i, val);
		}
	}
	else {
		while (count < m_size) {
			m_data[--m_size].T();
		}
	}
	m_size{ count };
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::swap(MyVector& other) noexcept {
	using std::swap;
	swap(m_size, other.m_size);
	swap(m_capacity, other.m_capacity);
	swap(m_data, other.m_data);
	swap(m_allocator, other.m_allocator);
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::m_allocate(size_t rsv_sz) {
	m_capacity{ rsv_sz };
	m_data{ m_allocator.allocate(m_capacity) };
}

template<typename T, class Allocator>
inline void MyVector<T, Allocator>::m_reallocate(size_t rsv_sz) {
	T* new_data{ m_allocator.allocate(rsv_sz) };
	memcpy(static_cast<void*>(new_data), static_cast<void*>(m_data), sizeof(T)* m_size);
	m_allocator.deallocate(m_data, m_capacity);
	m_capacity{ rsv_sz };
	m_data{ new_data };
}

template<typename T, class Allocator>
template<typename ...Args>
inline void MyVector<T, Allocator>::m_construct(size_t pos, Args&& ... args) {
	std::allocator_traits<Allocator>::construct(m_allocator, m_data + pos, std::forward<Args>(args) ...);
}
#endif // !MYVECTOR_HPP
