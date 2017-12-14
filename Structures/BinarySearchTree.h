#ifndef _BINARY_SEARCH_TREE_HEADER

#define _BINARY_SEARCH_TREE_HEADER

template <typename Type>
class BinaryTree
{
	struct Node
	{
		Node() : left(nullptr), right(nullptr), numberEl(1){};
		Node(const Type & newValue) : m_value(newValue), left(nullptr), right(nullptr), numberEl(1){};
		Type m_value;

		// This is a counter of the elements of the three which has for a root the current Node
		int numberEl;
		Node *left, *right;
	};

	Node * root;
public:
	BinaryTree() : root(nullptr){};
	BinaryTree(const Type & newValue)	{ root = new Node(newValue); }
	BinaryTree(const BinaryTree & right){ copy(right.root); }
	BinaryTree & operator=(const BinaryTree & right)
	{
		if (this != &right)
		{
			clear(root);
			copy(right.root);
		}
		return *this;
	}
	~BinaryTree(){ clear(root); }

	void insert(const Type & newValue) { bool inserted = false;  insert(root, newValue, inserted); }

	void print(){ print(root); }
	void printNumElem() { printNumElem(root); }
	void remove(const Type & forDeletionValue)	
	{
		bool elNumReduction = false;
		remove(root, forDeletionValue, elNumReduction);
	}
	bool find(const Type & searchEl){ return find(root, searchEl); }
	int numSubtreesWithNEl(int N)
	{
		int currentNum = 0;
		numSubtreesWithNEl(N, root, currentNum);
		return currentNum;
	}
	void getElementsFromTree(DynArray<Type> & arr){ getElementsFromTree(root, arr); }
	int getHight() { return getHight(root); }
	int getNumElem() { return root->numberEl; }
private:

	void copy(Node * current)
	{
		if (current == nullptr)
			return;
		insert(current->m_value);
		copy(current->right);
		copy(current->left);
	}

	void clear(Node *& current)
	{
		if (current == nullptr)
			return;

		bool elNumReduction = false;
		if (current->left != nullptr)
			clear(current->left);
		if (current->right != nullptr)
			clear(current->right);
		if (current->left == nullptr && current->right == nullptr)
			remove(current, current->m_value, elNumReduction);
	}

	void insert(Node *& current, const Type & newValue, bool & inserted)
	{
		if (current != nullptr)
		{
			if (current->m_value > newValue)
			{
				insert(current->left, newValue, inserted);
				if (inserted == true)
					++current->numberEl;
			}
			else if (current->m_value < newValue)
			{
				insert(current->right, newValue, inserted);
				if (inserted == true)
					++current->numberEl;
			}
			return;
		}
		current = new Node(newValue);
		inserted = true;
	}

	void print(Node * current)
	{
		if (current == nullptr)
			return;
		print(current->left);
		cout << current->m_value << " ";
		print(current->right);
	}

	// Prints number of elements of a three where the root is the currend element
	void printNumElem(Node * current)
	{
		if (current == nullptr)
			return;
		printNumElem(current->left);
		cout << current->numberEl << " ";
		printNumElem(current->right);
	}

	Node * minInThree(Node * current)
	{
		while (current->left != nullptr)
			current = current->left;
		return current;
	}

	// The parameter elNumReduction is to keep the number of elements in a subtree with root current.
	void remove(Node *& current, const Type & forDeletionValue, bool & elNumReduction)
	{
		if (current == nullptr)
			return;

		if (forDeletionValue > current->m_value)
		{
			remove(current->right, forDeletionValue, elNumReduction);
			if (elNumReduction == true)
				--current->numberEl;
			return;
		}
		else if (forDeletionValue < current->m_value)
		{
			remove(current->left, forDeletionValue, elNumReduction);
			if (elNumReduction == true)
				--current->numberEl;
			return;
		}
		if (current->left == nullptr && current->right == nullptr)
		{
			delete current;
			current = nullptr;
			elNumReduction = true;
			return;
		}
		else if (current->left != nullptr && current->right != nullptr)
		{
			Node * temp = minInThree(current->right);
			current->m_value = temp->m_value;
			remove(current->right, temp->m_value, elNumReduction);
			if (elNumReduction == true)
				--current->numberEl;
			return;
		}
		else if (current->left != nullptr || current->right != nullptr)
		{
			if (current->left != nullptr)
			{
				current->m_value = current->left->m_value;
				delete current->left;
				current->left = nullptr;
			}
			else if (current->right != nullptr)
			{
				current->m_value = current->right->m_value;
				delete current->right;
				current->right = nullptr;
			}
			elNumReduction = true;
			return;
		}
	}

	bool find(Node * current, const Type & searchEl)
	{
		if (current == nullptr)
			return false;
		if (current->m_value > searchEl)
			return find(current->left, searchEl);
		else if (current->m_value < searchEl)
			return find(current->right, searchEl);
		return true;
	}

	void numSubtreesWithNEl(int N, Node * current, int & currentNum)
	{
		if (current == nullptr)
			return;
		numSubtreesWithNEl(N, current->left, currentNum);
		numSubtreesWithNEl(N, current->right, currentNum);
		if (current->numberEl == N)
			++currentNum;
	}

	void getElementsFromTree(Node * current, DynArray<Type> & arr)
	{
		if (current == nullptr)
			return;
		getElementsFromTree(current->left, arr);
		arr.insert(current->m_value);
		getElementsFromTree(current->right, arr);
	}

	int getHight(Node * current)
	{
		int left, right;
		if (current == nullptr)
			return -1;
		left = getHight(current->left);
		right = getHight(current->right);
		return left > right ? left + 1: right + 1;
	}

	// Mine code:
	/*void getHight(Node * current, int left, int right, int & result)
	{
		if (current == nullptr)
			return;
		getHight(current->left, ++left, right, result);
		getHight(current->right, left, ++right, result);
		if (left > result || right > result)
			result = left > right ? left : right;
	}*/
	
};



#endif // !_BINARY_SEARCH_THREE_HEADER
