#ifndef BST_IN_ORDER_ITERATOR
#define BST_IN_ORDER_ITERATOR

#include "BinaryNode.h"
#include <vector>
#include <iterator>
using namespace std;
template <typename T>
class BstInOrderIterator : public iterator<forward_iterator_tag, T>
{
private:
	vector<BinaryNode<T> *> _to_visit;
	int _current_node = 0;

	//Want a fun challenge?  Make this inline with operator*().  In other
	//words, don't prep the _to_visit stack before hand 
	//(change from O(2N) to O(N) traversal time)
	void buildVisitList(BinaryNode<T> *root)
	{
		if (root != nullptr)
		{
			buildVisitList(root->getLeftChild());
			_to_visit.push_back(root);
			buildVisitList(root->getRightChild());
		}
	}

public:

	BstInOrderIterator(BinaryNode<T> *root, bool is_end = false)
	{
		buildVisitList(root);
		if (is_end == true)
		{
			_current_node = _to_visit.size();
		}
	}

	BstInOrderIterator(const BstInOrderIterator &other)
	{
		//copy over other's contents
		_to_visit = other._to_visit;
		_is_end = other._is_end;
	}

	//for ++iter
	BstInOrderIterator & operator++()
	{
		++_current_node;
		return *this;
	}

	//for iter++ 
	BstInOrderIterator operator++(int)
	{
		BstInOrderIterator tmp{ *this };
		operator++();
		return tmp;
	}

	//for comparisons
	bool operator==(const BstInOrderIterator<T> &other)
	{
		return _current_node == other._current_node;
	}

	bool operator!=(const BstInOrderIterator<T> &other)
	{
		return _current_node != other._current_node;
	}

	//for actually getting values from the iterator
	T &operator*()
	{
		if (_current_node < _to_visit.size())
		{
			return _to_visit[_current_node]->getValue();
		}
		else
		{
			return _to_visit[_to_visit.size() - 1]->getValue();
		}
	}

	//needed for comparisons and const operations
	const T &operator*() const
	{
		if (_current_node < _to_visit.size())
		{
			return _to_visit[_current_node]->getValue();
		}
		else
		{
			return _to_visit[_to_visit.size() - 1]->getValue();
		}
	}
};


#endif