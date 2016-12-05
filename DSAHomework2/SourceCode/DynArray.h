#ifndef _DYN_ARRAY_HEADER


#define _DYN_ARRAY_HEADER 

#include <cassert>
template <typename TYPE>
class DynArray
{
	TYPE *m_arr;
	int m_size;
	int m_capacity;

public:

	DynArray() : m_arr(nullptr), m_size(0), m_capacity(0){}

	DynArray(const DynArray & right) { copy(right); }

	DynArray & operator= (const DynArray & right)
	{
		if (this != &right)
		{
			delete[] m_arr;
			copy(right);
		}
		return *this;
	}

	~DynArray() { delete[] m_arr; }

	const int getSize() const { return m_size; }

	int getCapacity() { return m_capacity; }
	const TYPE * getArr() const	{ return m_arr; }

	void copy(const DynArray & right);
	void resize(int newCapacity);

	void addAtEnd(const TYPE & newElement);		//Add element at the end
	void pop();							//Remove element from the end

	TYPE &lastElem(){ return m_arr[m_size - 1]; } //returns last element of the array

	void addAtIndex(int index)
	{
		if (index < 0 || index >= m_capacity)
			throw "Bad index at addAtIndex funciton!!!\n";
		if (m_capacity == 0)
			resize(5);
		if (m_capacity == m_size)
			resize(m_capacity * 2);

		m_arr[index] = newElement;
		if (index >= size)
			++m_size;
	}

	void print()
	{
		int size = m_size;
		for (int i = 0; i < size; ++i)
		{
			cout << m_arr[i] << endl;
		}
	}

	void cleanArray()
	{
		delete[] m_arr;
		m_arr = NULL;
		m_size = 0;
		m_capacity = 0;
	}

	TYPE & operator[](int index)
	{
		assert(index >= 0 && index < m_size);

		return m_arr[index];
	}

	const TYPE  & operator[] (int index) const		// for const objects, can only be used for access
	{
		assert(index >= 0 && index < m_size);

		return m_arr[index];
	}



};


// I will make the functions inlined because this header can be included in more than one cpp


template <typename TYPE>
inline void DynArray<TYPE>::copy(const DynArray & right)
{
	m_arr = new TYPE[right.m_capacity];
	m_capacity = right.m_capacity;
	m_size = right.m_size;
	for (int i = 0; i < m_size; ++i)
		m_arr[i] = right.m_arr[i];

}


template <typename TYPE>
inline void DynArray<TYPE>::resize(int newCapacity)
{
	TYPE * temp = new TYPE[newCapacity];

	for (int i = 0; i < m_capacity; ++i)
		temp[i] = m_arr[i];

	delete[]m_arr;

	m_arr = temp;
	m_capacity = newCapacity;
}


template <typename TYPE>
inline void DynArray<TYPE>::addAtEnd(const TYPE & newElement)
{
	if (m_capacity == 0)
		resize(5);
	if (m_capacity == m_size)
		resize(m_capacity * 2);

	m_arr[m_size] = newElement;
	++m_size;
}

template <typename TYPE>
inline void DynArray<TYPE>::pop()
{
	if (m_capacity == 0)
		return;
	if (m_capacity / 3 >= m_size)
		resize(m_capacity / 2);
	--size;
}


#endif // !_DYN_ARRAY_HEADER
