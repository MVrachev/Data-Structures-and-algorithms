#ifndef _STACK_HEADER

#define _STACK_HEADER

#include "DynArray.h"

template <typename Type>
class Stack
{
	DynArray<Type> m_arr;
public:
	Stack(){};
	Stack(const Stack & right){ m_arr = right.m_arr; }
	Stack & operator = (const Stack & right)
	{
		if (this != &right)
		{
			m_arr = right.m_arr;
		}
	};
	~Stack(){};

	void push(const Type & newValue) {	m_arr.insert(newValue);	}
	void pop() { m_arr.remove(); }
	bool isEmpty() { return m_arr.getSize() == 0 ? true : false; }
	int size() { return m_arr.getSize(); }
	Type & top() { return m_arr[size() - 1]; }

	void print() { cout << m_arr << endl; }
};


#endif // !_STACK_HEADER
