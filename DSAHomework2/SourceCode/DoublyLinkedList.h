#ifndef _DOUBLY_LINKED_LIST_HEADER

#define _DOUBLY_LINKED_LIST_HEADER

#include <iostream>
using namespace std;

template <typename TYPE>
class DoublyLinkedList
{
	struct Node
	{
		TYPE m_data;
		Node *m_next, *m_previous;
		Node() : m_data(), m_next(nullptr), m_previous(nullptr){};
		Node(const TYPE &newData) : m_data(newData), m_next(nullptr), m_previous(nullptr) {}
	};

	Node *m_back, *m_front;

public:

	DoublyLinkedList() : m_back(nullptr), m_front(nullptr){}

	DoublyLinkedList(const TYPE &newData)
	{
		Node * newElem = new Node(newData);
		m_back = newElem;
		m_front = m_back;
		//m_size = 1;
	}

	DoublyLinkedList(const DoublyLinkedList & right)
	{
		copy(right);
	}

	DoublyLinkedList & operator=(const DoublyLinkedList &right)
	{
		if (this != &right)
		{
			clear();
			copy(right);
		}
		return *this;
	}

	~DoublyLinkedList() { clear(); }

	void copy(const DoublyLinkedList & right);

	void clear()
	{
		while (!isEmpty())
		{
			removeFirstElem();
		}
	}

	void print(); // only for testing

	class Iterator
	{
		Node *m_ptr;
	public:
		Iterator() : m_ptr(nullptr) {}

		Iterator(TYPE newData) { m_ptr->m_data = newData; }

		Iterator(Node *newPtr)	{ m_ptr = newPtr; }

		Iterator(const Iterator & right) { m_ptr = right.m_ptr; }


		Iterator & operator = (const Iterator &right)
		{
			if (this !&= right)
			{
				m_ptr = right.m_ptr;
			}
			return *this;
		}

		Node * getIteratorPtr() { return m_ptr; }

		TYPE & operator*() { return m_ptr->m_data; }

		TYPE * operator->() { return &m_ptr->m_data; }

		bool operator == (const Iterator&right)	{ return m_ptr == right.m_ptr; }
		bool operator !=(const Iterator& right) { return m_ptr != right.m_ptr; }


		Iterator & operator++()   // ++it
		{
			m_ptr = m_ptr->m_next;
			return *this;
		}

		Iterator operator++(int) // it++
		{
			Iterator temp(*this);
			m_ptr = m_ptr->m_next;
			return temp;
		}

		Iterator & operator--()   // --it
		{
			m_ptr = m_ptr->m_previous;
			return *this;
		}

		Iterator operator--(int) // it--
		{
			Iterator temp(*this);
			m_ptr = m_ptr->m_previous;
			return temp;
		}

	};

	void removeFirstElem();

	void addAtEnd(const TYPE & newData);

	bool isEmpty()
	{
		return m_front == nullptr ? true : false;
	}


	Iterator begin()
	{
		return Iterator(m_front); // this is because if the begin iterator is m_back it will be printed reversed
	}

	Iterator end()
	{
		return Iterator();
	}

	// Const versions of begin and end for const objects. This is needed firstly because of the copy function.

	Iterator begin() const
	{
		return Iterator(m_front);
	}

	Iterator end() const
	{
		return Iterator();
	}



};


template <typename TYPE>
void DoublyLinkedList<TYPE>::copy(const DoublyLinkedList & right)
{
	Iterator beginIt = right.begin();
	Iterator endIt = right.end();
	for (; beginIt != endIt; --beginIt)
	{
		this->addAtEnd(*beginIt);
	}
}

template <typename TYPE>
void DoublyLinkedList<TYPE>::addAtEnd(const TYPE & newData)
{
	if (isEmpty())
	{
		Node *newElem = new Node(newData);
		m_front = newElem;
		m_back = newElem;
	}
	else
	{
		Node *newElemPtr = new Node(newData);
		newElemPtr->m_next = m_back;
		m_back->m_previous = newElemPtr;
		newElemPtr->m_previous = nullptr;
		m_back = newElemPtr;
	}
}

template <typename TYPE>
void DoublyLinkedList<TYPE>::removeFirstElem()
{
	if (isEmpty())
		return;
	if (m_front->m_previous == nullptr)
	{
		delete m_front;
		m_front = nullptr;
		m_back = nullptr;
	}
	else
	{
		Node *temp = m_front->m_previous;
		delete m_front;
		m_front = temp;
		m_front->m_next = nullptr;
	}
}

template <typename TYPE>
void DoublyLinkedList<TYPE>::print()  // just for testing purposes
{
	Iterator begIt(begin());
	Iterator endIt(end());
	int index = 0;
	for (; begIt != endIt; --begIt)
	{
		cout << "Element " << index << " is: " << *begIt << endl;
		++index;
	}
	cout << endl;
}


#endif // !_DOUBLY_LINKED_LIST_HEADER
