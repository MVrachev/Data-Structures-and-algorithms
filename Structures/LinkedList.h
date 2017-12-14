#ifndef LINKED_LIST_HEADER

#define LINKED_LIST_HEADER


// A single linked list with pointers to the begin and the end of the list
// Insert at the begging for O(1) and remove from the beggin for O(1)
// and remove from the end for O(n).

template<typename Type>
class LinkedList
{
	struct Node
	{
		Node() : m_next(nullptr){}
		Node(const Type & newValue) : m_value(newValue), m_next(nullptr){}
		Type m_value;
		Node * m_next;
	};

	Node *m_begin, *m_end;
	int m_size;
public:


	LinkedList() : m_begin(nullptr), m_end(nullptr), m_size(0){};
	LinkedList(const LinkedList & right)	{	copy(right);	}
	LinkedList & operator=(const LinkedList & right)
	{
		if (this != &right)
		{
			clear();
			copy(right);
		}
		return *this;
	}
	~LinkedList()	{	clear();	}

	int getSize() { return m_size; }
	const int getSize() const { return m_size; }

	// Inserts at the begging.
	void insert(const Type & newValue)
	{
		Node * newElement = new Node(newValue);
		if (m_begin == nullptr)
		{
			m_begin = newElement;
			m_end = newElement;
		}
		else
		{
			newElement->m_next = m_begin;
			m_begin = newElement;
		}
		++m_size;
	}

	// Deletes for O(1) from the begging and O(n) in the end
	void remove(const Type & forDeletion)
	{
		if (m_begin->m_value == forDeletion)
		{
			Node * t = m_begin;
			m_begin = m_begin->m_next;
			delete t;
			return;
		}
		Node * curr = m_begin;
		while (curr->m_next != nullptr && curr->m_next->m_value != forDeletion)
			curr = curr->m_next;
		if (curr->m_next != nullptr)
		{
			Node * t = curr->m_next;
			curr->m_next = t->m_next;
			delete t;
		}
		--m_size;
	}

	void print()
	{
		Node * curr = m_begin;
		while (curr != nullptr)
		{
			cout << curr->m_value << " ";
			curr = curr->m_next;
		}
		cout << endl;
	}

	void reverse(LinkedList & result) const
	{
		Node *current = m_begin;
		while (current != nullptr)
		{
			result.insert(current->m_value);
			current = current->m_next;
		}
	}

	class Iterator
	{
		Node *pointer;
	public:
		Iterator() : pointer(nullptr){};
		Iterator(Node * pointTo) : pointer(pointTo){}
		Iterator(const Iterator & right) { pointer = right.pointer; }
		Iterator & operator=(const Iterator & right)
		{
			if (this != &right)
			{
				pointer = right.pointer;
			}
			return *this;
		}
		~Iterator(){}

		Type & operator*()
		{
			return pointer->m_value;
		}

		const Type & operator*() const
		{
			return pointer->m_value;
		}

		Type* operator->()
		{
			return &pointer->m_value;
		}

		const Type* operator->() const
		{
			return &pointer->m_value;
		}

		Iterator & operator++() // like: ++a
		{
			pointer = pointer->m_next;
			return *this;
		}

		Iterator operator++(int) // like: a++
		{
			Iterator result(*this);
			++(*this);
			return result;
		}

		bool operator==(const Iterator & right) { return pointer == right.pointer; }
		bool operator!=(const Iterator & right) { return !((*this) == right); }

		const bool isItAvailable() const { return pointer != nullptr; }

		bool isItAvailable() { return pointer != nullptr; }

		const bool isThereNext() const  { return pointer->m_next != nullptr; }

		bool isThereNext() { return pointer->m_next != nullptr; }

		const Node * getPointer() const  { return pointer; }
		Node * getPointer() { return pointer; }
	private:
		Node * getNode(){ return pointer; }
		const Node * getNode() const { return pointer; }

		void setPtr(Node * ptr) { pointer = ptr; }

		Node * findNode(const Type & searchedValue)
		{
			Node * curr = m_begin;
			while (curr != nullptr)
			{
				if (curr->m_value == searchedValue)
					return Iterator(curr);
				curr = curr->m_next;
			}
		}
	};

	Iterator begin() {	return Iterator(m_begin);	}
	Iterator  end()  {	return Iterator(m_end);		}

	const Iterator begin() const { return Iterator(m_begin); }
	const Iterator end() const { return Iterator(m_end); }

	// Returns iterator to the first node with that value
	Iterator find(const Type & searchedValue)
	{
		Node * curr = m_begin;
		while (curr != nullptr)
		{
			if (curr->m_value == searchedValue)
				return Iterator(curr);
			curr = curr->m_next;
		}
		return Iterator();
	}
	
	void insertAfter(Iterator & elem, const Type & newValue)
	{
		// There is only one case when elem wont be available: when there are no elements
		// in the linked list
		if (!elem.isItAvailable())
		{
			insert(newValue);
		}
		else
		{
			Node * newElem = new Node(newValue);
			Node * curr = elem.getPointer();
			Node *next = curr->m_next;
			curr->m_next = newElem;
			newElem->m_next = next;
			++elem;
		}
	}
	
private:
		void copy(const LinkedList & right)
		{
			LinkedList<Type> temp;
			right.reverse(temp);
			temp.reverse(*this);
			m_size = right.m_size;
		}

		void clear()
		{
			while (m_begin != nullptr)
			{
				Node *t = m_begin->m_next;
				if (t != nullptr)
					m_begin->m_next = t->m_next;
				else
				{
					delete m_begin;
					m_begin = nullptr;
				}
				delete t;
			}
			m_size = 0;
		}


};



#endif // !LINKED_LIST_HEADER
