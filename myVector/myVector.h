#ifndef MYVECTOR_H
#define MYVECTOR_H

template<typename T, class Allocator = std::allocator<T>>
class MyVector {
public:
	//	Constructor, Destructor, Asignment
	MyVector() noexcept;
	explicit MyVector(const Allocator& alloc) noexcept;
	explicit MyVector(size_t count, const Allocator& alloc = Allocator());
	explicit MyVector(size_t count, const T& value, const Allocator& alloc = Allocator());
	MyVector(const MyVector& other);
	MyVector(const MyVector& other, const Allocator& alloc);
	MyVector(MyVector&& other) noexcept;
	MyVector(const MyVector&& other, const Allocator& alloc);
	MyVector(std::initializer_list<T> init, const Allocator& alloc = Allocator());
	~MyVector();
	MyVector& operator=(const MyVector& other);
	MyVector& operator=(MyVector&& other) noexcept;
	MyVector& operator=(std::initializer_list<T> init);

	//Element access
	T& operator[](size_t pos);
	const T& operator[](size_t pos) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T* data() noexcept;
	const T* data() const noexcept;

	//	Iterators
	T* begin() noexcept;
	const T* begin()const noexcept;
	T* end() noexcept;
	const T* end()const noexcept;

	//	Capacity
	bool empty() const noexcept;
	size_t size() const noexcept;
	size_t capacity() const noexcept;
	void reserve(size_t new_cap);

	//	Modifiers
	void clear() noexcept;
	T* insert(const T* pos, const T& val);
	T* erase(const T* pos);
	void push_back(const T& val);
	void pop_back();
	void resize(size_t count);
	void resize(size_t size, const T& val);
	void swap(MyVector& other) noexcept;
	
private:
	size_t m_capacity{ constants::default_size };
	size_t m_size{ 0 };
	Allocator m_allocator;
	T* m_data{ nullptr };
	void m_allocate(size_t rsv_sz);
	void m_reallocate(size_t rsv_sz);
	template<typename ...Args> void m_construct(size_t pos, Args&& ... args);
};

#include "myVector.hpp"

#endif // !MYVECTOR_H
