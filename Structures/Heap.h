#ifndef _HEAP_HEADER

#define _HEAP_HEADER

#include "DynArray.h"

// This is max heap
template <typename Type>
class Heap
{
	DynArray<Type> m_arr;
	int m_size;
public:
	Heap(): m_size(0) {};
	~Heap(){};

	void insert(const Type & newValue)
	{
		m_arr.insert(newValue);
		++m_size;
		heapifyUp(newValue);
	}

	void print(){ cout << m_arr << endl; }
	Type extractMax() 
	{
		Type result = m_arr[0];
		m_arr[0] = m_arr[m_size - 1];
		m_arr[m_size - 1] = result;
		--m_size;
		m_arr.remove();
		heapifyDown();
		return result;
	}

	bool isEmpty() { return m_size == 0; }
	int getSize() { return m_size; }

	const bool isEmpty() const { return m_size == 0; }
	const int getSize() const { return m_size; }
private:

	void heapifyUp(const Type & newValue)
	{
		int fatherIndex = (m_size - 1) / 2, newElIndex = m_size - 1;
		Type temp;
		while (fatherIndex >= 0 && m_arr[fatherIndex] < m_arr[newElIndex])
		{
			temp = m_arr[fatherIndex];
			m_arr[fatherIndex] = m_arr[newElIndex];
			m_arr[newElIndex] = temp;
			newElIndex = fatherIndex;
			fatherIndex = (newElIndex - 1) / 2;
		}
	}

	void heapifyDown()
	{
		int fatherIndex = 0, firstKid = 2 * fatherIndex + 1, secondKid = 2 * fatherIndex + 2;
		int biggerKid = firstKid;
		Type temp;
		while (firstKid < m_size)
		{
			if (secondKid < m_size)
			{
				biggerKid =
					m_arr[firstKid] > m_arr[secondKid] ? firstKid : secondKid;
			}
			temp = m_arr[fatherIndex];
			m_arr[fatherIndex] = m_arr[biggerKid];
			m_arr[biggerKid] = temp;
			fatherIndex = biggerKid;
			firstKid = 2 * fatherIndex + 1;
			secondKid = 2 * fatherIndex + 2;
			biggerKid = firstKid;
		}
	}
};


#endif // !_HEAP_HEADER
