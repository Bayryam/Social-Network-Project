#pragma once
#include<iostream>

const size_t DEFAULT_CAPACITY = 8;

template <typename T>
class MyVector {
private:
	T* data;
	size_t size;
	size_t capacity;

	void copyFrom(const MyVector& other);
	void free();
	void moveFrom(MyVector&& other);
	void resize();
public:
	MyVector();
	MyVector(const MyVector<T>& other);
	MyVector(MyVector<T>&& other);
	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other);
	~MyVector();

	size_t getSize() const;
	size_t getCapacity() const;

	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(const T& element, size_t index);
	void pushAt(T&& element, size_t index);
	T& popBack();
	T& popAt(size_t index);
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	bool empty() const;
	void clear();
};

template <typename T>
void MyVector<T>::copyFrom(const MyVector& other)
{
	size = other.getSize();
	capacity = other.getCapacity();
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}
template <typename T>
void MyVector<T>::free()
{
	delete[] data;
	size = capacity = 0;
	data = nullptr;
}
template <typename T>
void MyVector<T>::moveFrom(MyVector&& other)
{
	data = other.data;
	size = other.getSize();
	capacity = other.getCapacity();
	other.data = nullptr;
	other.size = other.capacity = 0;
}
template<typename T>
void MyVector<T>::resize()
{
	capacity *= 2;
	T* newData = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
}


template <typename T>
MyVector<T>::MyVector()
{
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
	size = 0;
}
template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}
template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other)
{
	moveFrom(std::move(other));
}
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other)
{
	if (this != &other)
	{
		free();
		copyFrom(std::move(other));
	}
	return *this;
}
template <typename T>
MyVector<T>::~MyVector()
{
	free();
}

template <typename T>
size_t MyVector<T>::getSize() const
{
	return size;
}
template <typename T>
size_t MyVector<T>::getCapacity() const
{
	return capacity;
}

template <typename T>
void MyVector<T>::pushBack(const T& element)
{
	if (size == capacity)
	{
		resize();
	}
	data[size++] = element;
}
template <typename T>
void MyVector<T>::pushBack(T&& element)
{
	if (size == capacity)
	{
		resize();
	}
	data[size++] = std::move(element);
}
template<typename T>
void MyVector<T>::pushAt(const T& element, size_t index)
{
	if (index <0 || index > size - 1)
		throw std::out_of_range;

	if (size == capacity)
		resize();

	for (int i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = element;
	size++;
}
template<typename T>
void MyVector<T>::pushAt(T&& element, size_t index)
{
	if (index <0 || index > size - 1)
		throw std::out_of_range;

	if (size == capacity)
		resize();

	for (int i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = std::move(element);
	size++;
}
template <typename T>
T& MyVector<T>::popBack()
{
	if (empty())
		throw std::out_of_range;
	size--;
	return data[size];
}
template<typename T>
T& MyVector<T>::popAt(size_t index)
{
	if (index <0 || index > size - 1)
		throw std::out_of_range;
	T res = data[index];
	for (size_t i = index; i < size-1; i++)
	{
		data[i] = data[i + 1];
	}
	size--;
	return res;
}
template<typename T>
T& MyVector<T>::operator[](size_t index) 
{
	if (index <0 || index > size - 1)
		throw std::out_of_range;
	return data[index];
}
template<typename T>
const T& MyVector<T>::operator[](size_t index) const 
{
	if (index <0 || index > size - 1)
		throw std::out_of_range;
	return data[index];
}
template<typename T>
bool MyVector<T>::empty() const 
{
	return size == 0;
}
template<typename T>
void MyVector<T>::clear() 
{
	delete[] data;
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
	size = 0;
}

