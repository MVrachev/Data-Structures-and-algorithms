#ifndef _QUEUE_HEADER

#define _QUEUE_HEADER

 #include "DoubleLinkedList.h"

template <typename Type>
class Queue
{
	DoubleLinkedList<Type> list;
public:
	Queue(){};
	~Queue(){};

	void push(const Type & newValue) {	list.insertInFront(newValue); }
	void pop()	{ list.removeBack(); }
	bool isEmpty() { return list.getSize() == 0; }
	int getSize() { return list.getSize(); }
	void print() { list.printWithBack(); }
};



#endif // !_QUEUE_HEADER
