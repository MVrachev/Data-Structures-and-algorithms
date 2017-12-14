#ifndef _DOUBLE_LINKED_LIST

#define _DOUBLE_LINKED_LIST

template <typename Type>
class DoubleLinkedList
{
	struct Node
	{
		Node() : m_next(nullptr), m_prev(nullptr){}
		Node(const Type & newValue) : m_next(nullptr), m_prev(nullptr), m_value(newValue){};
		Type m_value;
		Node *m_next, *m_prev;
	};
	Node *m_beg, *m_end;
	int m_size;
public:
	DoubleLinkedList() :m_beg(nullptr), m_end(nullptr), m_size(0){};
	DoubleLinkedList(const DoubleLinkedList & right) { copy(right); }
	DoubleLinkedList & operator=(const DoubleLinkedList & right)
	{
		if (this != &right)
		{
			clear();
			copy(right);
		}
		return *this;
	}
	~DoubleLinkedList() { clear(); }

	int getSize() { return m_size; }
	const int getSize() const { return m_size; }

	void insertInFront(const Type & newValue)
	{
		Node * newEl = new Node(newValue);
		if (insertCornerCases(newEl) == true)
			return;
		Node * temp = m_beg;
		newEl->m_next = temp;
		temp->m_prev = newEl;
		m_beg = newEl;
		++m_size;
	}

	void insertInBack(const Type & newValue)
	{
		Node * newEl = new Node(newValue);
		if (insertCornerCases(newEl, false) == true)
			return;
		Node *temp = m_end;
		m_end = newEl;
		m_end->m_prev = temp;
		temp->m_next = m_end;
		++m_size;
	}

	void removeFront()
	{
		if (m_beg == nullptr)
			return;
		Node * t = m_beg;
		// To be sure that if there is one node left 
		// both end and begin will point in a special place: nullptr
		if (m_end == m_beg)
			m_end = nullptr;

		m_beg = m_beg->m_next;
		if (m_beg != nullptr)
			m_beg->m_prev = nullptr;
		delete t;
		--m_size;
	}

	void removeBack()
	{
		if (m_end == nullptr)
			return;
		Node *t = m_end;
		// To be sure that if there is one node left 
		// both end and begin will point in a special place: nullptr
		if (m_end == m_beg)
			m_beg = nullptr;
		m_end = m_end->m_prev;
		if (m_end != nullptr)
			m_end->m_next = nullptr;
		delete t;
		--m_size;
	}

	// Deletes a node with particular value. For O(1) if it is from the end
	// or the begging otherwise is for O(n).
	void removeAnElement(const Type & deleteValue)
	{
		if (m_beg->m_value == deleteValue)
		{
			Node * t = m_beg;
			m_beg->m_next->m_prev = nullptr;
			m_beg = m_beg-> m_next;
			delete t;
			return;
		}
		if (m_end->m_value == deleteValue)
		{
			Node * t = m_end;
			m_end->m_prev->m_next = nullptr;
			m_end = m_end->m_prev;
			delete t;
			return;
		}
		Node * current = m_end->m_prev;
		while (current != nullptr)
		{
			if (current->m_value == deleteValue)
			{
				Node *t = current;
				current = current->m_next;
				t->m_prev->m_next = current;
				current->m_prev = t->m_prev;
				delete t;
				return;
			}
			current = current->m_prev;
		}
		--m_size;
	}

	void printWithNext()
	{
		Node * curr = m_beg;
		while (curr != nullptr)
		{
			cout << curr->m_value << " ";
			curr = curr->m_next;
		}
		cout << endl;
	}
	
	void printWithBack()
	{
		Node *curr = m_end;
		while (curr != nullptr)
		{
			cout << curr->m_value << " ";
			curr = curr->m_prev;
		}
		cout << endl;
	}

	class Iterator
	{
		Node * m_ptr;
	public:
		Iterator() : m_ptr(nullptr){};
		~Iterator();
		
		Type* operator->()
		{
			return &m_ptr->m_value;
		}

		const Type* operator->() const
		{
			return &m_ptr->m_value;
		}

		Type & operator*()
		{
			return m_ptr->m_value;
		}

		const Type & operator*() const
		{
			return m_ptr->m_value;
		}

		Iterator & operator++()		// like ++a
		{
			m_ptr = m_ptr->m_next;
			return *this;
		}

		Iterator operator++(int)	// like: a++
		{
			Iterator result(*this);
			++(*this);
			return result;
		}

		Iterator & operator--()		// like --a
		{
			m_ptr = m_ptr->m_prev;
			return *this;
		}
		Iterator operator--(int)	// like a--
		{
			Iterator result(*this);
			--(*this);
			return result;
		}

		bool operator==(const Iterator & right)		{	return m_ptr == right.m_ptr;	}
		
		bool operator != (const Iterator & right)	{	return !((*this) == right);	}

		const bool isItAvailable() const { return pointer != nullptr; }

		bool isItAvailable() { return pointer != nullptr; }

		bool isThereNext()	{ return m_ptr->m_next != nulltr; }
		
		const bool isThereNext() const	{ return m_ptr->m_next != nulltr; }

		bool isTherePrev()	{ return m_ptr->m_prev != nulltr; }

		const bool isTherePrev() const	{ return m_ptr->m_prev != nulltr; }
	};

	

private:
	void clear()
	{
		Node * temp = m_beg;
		while (m_beg != nullptr)
		{
			temp = m_beg;
			m_beg = m_beg->m_next;
			delete temp;
		}
		m_size = 0;
	}

	void copy(const DoubleLinkedList & right)
	{
		Node *curr = right.m_end;
		while (curr != nullptr)
		{
			insertInFront(curr->m_value);
			curr = curr->m_prev;
		}
		m_size = right.m_size;
	}

	// It's for corner cases for both inserts: front and end
	bool insertCornerCases(Node * newEl, bool frontInsert = true)
	{
		if (m_beg == nullptr)
		{
			m_beg = newEl;
			m_end = newEl;
			return true;
		}
		else if (m_beg == m_end && frontInsert == true)
		{
			m_beg = newEl;
			m_beg->m_next = m_end;
			m_end->m_prev = newEl;
			return true;
		}
		else if (m_beg == m_end && frontInsert == false)
		{
			m_end = newEl;
			m_beg->m_next = m_end;
			m_end->m_prev = m_beg;
			return true;
		}
		return false;
	}
};



#endif // !_DOUBLE_LINKED_LIST
