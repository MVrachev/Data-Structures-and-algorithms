#ifndef _QUEUE_HEADER

#define _QUEUE_HEADER

#include "DoublyLinkedList.h"


template <typename TYPE>
class Queue
{
	DoublyLinkedList<TYPE> linkedItems;
public:

	Queue() : linkedItems(){}

	Queue(const Queue & right) { linkedItems.copy(right.linkedItems); }

	Queue & operator = (const Queue &right)
	{
		if (this != &right)
		{
			linkedItems.clear();
			linkedItems.copy(right.linkedItems);
		}
		return *this;
	}
	~Queue(){}

	void clear()
	{
		linkedItems.clear();
	}
	void push(const TYPE & newData) { linkedItems.addAtEnd(newData); } // Adds an item onto the end of the queue.


	TYPE &front() { return *(linkedItems.begin()); } // Returns the item at the front of the queue.

	void pop()	{ linkedItems.removeFirstElem(); } //Removes the item from the front of the queue.
	bool isEmpty() { return linkedItems.isEmpty(); }   //True if no more items can be dequeued and there is no front item.

	void print() { linkedItems.print(); }  // only for testing purposes
};



#endif // !_QUEUE_HEADER
