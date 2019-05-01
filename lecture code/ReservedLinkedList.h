#ifndef RESERVED_LINKED_LIST_H
#define RESERVED_LINKED_LIST_H

#include "LinkedList.h"
#include "Indexed.h"

template <typename T>
class ReservedLinkedList : public LinkedList<T>
{
private:
	ListNode<T> *_free_store = nullptr;
	int _free_node_count = 0;

protected:

	//where the magic happens
	virtual ListNode<T> *createNode(T value)
	{
		if (_free_store == nullptr)
		{
			return new ListNode<T>{ value };
		}
		else
		{
			ListNode<T> *some_node = _free_store;
			_free_store = _free_store->getNext();
			_free_node_count--;
			return some_node;
		}
	}

	virtual void deleteNode(ListNode<T> *node)
	{
		if (_free_node_count < getSize() / 2)
		{
			node->setNext(_free_store);
			_free_store = node;
			_free_node_count++;
		}
		else
		{
			delete node;
		}
	}

public:

	virtual ~ReservedLinkedList()
	{
		while (_free_store != nullptr)
		{
			ListNode<T> *current = _free_store->getNext();
			delete _free_store;
			_free_store = current;
		}
	}
};

#endif