#ifndef OLD_LINKED_LIST_H
#define OLD_LINKED_LIST_H

#include <stdexcept>
#include "Indexed.h"
#include "ListNode.h"
#include <utility>
using namespace std;

template <typename T>
class OldLinkedList : public Indexed<T>
{
private:

	//points to the front of the linked list
	ListNode<T> *_front = nullptr;
	ListNode<T> *_end = nullptr;

	//2014-07-07 CLASS TODO: Implement "last accessed" node

	//keeping track of size in a variable eliminates need to continually
	//count LL boxes.
	int _size = 0;


protected:
	ListNode<T> *getFront()
	{
		return _front;
	}

	ListNode<T> *getEnd()
	{
		return _end;
	}

	virtual ListNode<T> *createNode(T value)
	{
		return new ListNode<T>{ value };
	}

	virtual void deleteNode(ListNode<T> *node)
	{
		delete node;
	}

	//index.
	ListNode<T> *getNodeAtIndex(int index)
	{
		//check to see if index is valid
		if (index < 0 || index >= getSize())
		{
			throw out_of_range("Invalid index.");
		}

		//tracks the number of node hops
		//option #1
		ListNode<T> *current = _front;
		for (int i = 0; i < index; i++)
		{
			current = current->getNext();
		}
		return current;
	}

	//constant version of the above code
	const ListNode<T> *getNodeAtIndex(int index) const
	{
		//check to see if index is valid
		if (index < 0 || index >= getSize())
		{
			throw out_of_range("Invalid index.");
		}

		//tracks the number of node hops
		//option #1
		ListNode<T> *current = _front;
		for (int i = 0; i < index; i++)
		{
			current = current->getNext();
		}
		return current;
	}

public:

#pragma region constructor - destructor - operator=


	OldLinkedList()
	{
		_front = nullptr;
		_end = _front;
	}

	//copy constructor
	OldLinkedList(const LinkedList<T> &other)
	{
		for (int i = 0; i < other.getSize(); i++)
		{
			addElement(other.getElementAt(i));
		}
	}

	//Always remeber to clean up pointers in destructor
	virtual ~OldLinkedList()
	{
		ListNode<T> *current = _front;
		ListNode<T> *next = nullptr;
		while (current != nullptr)
		{
			next = current->getNext();
			delete current;
			current = next;
		}
	}

	LinkedList<T> &operator=(const LinkedList<T> &other)
	{
		//action item #1: delete current state
		ListNode<T> *current = _front;
		ListNode<T> *next = nullptr;
		while (current != nullptr)
		{
			next = current->getNext();
			delete current;
			current = next;
		}

		//zero out our internal state
		_front = nullptr;
		_size = 0;

		//copy state from other LL
		for (int i = 0; i < other.getSize(); i++)
		{
			addElement(other.getElementAt(i));
		}
	}
#pragma endregion

#pragma region Collection overrides

	//will return true if the LL is empty.
	virtual bool isEmpty() const
	{
		return _size == 0;
	}

	//returns the size of the LL.
	virtual int getSize() const
	{
		return _size;
	}

	//adds the supplied item to the end of our LL
	virtual void addElement(T value)
	{
		addElementAt(value, getSize());
	}
#pragma endregion

#pragma region Indexed overrides

	//returns the value at the specified index
	virtual T& getElementAt(int location)
	{
		//explicit way
		//ListNode<T> *result = getNodeAtIndex(location);
		//return result->getValue();

		//shortcut
		//this is called "method chaining" and can go on forever:
		//getNodeAtIndex(location)->getNext()->getNext()->getNext()
		///usually, not the best idea
		return getNodeAtIndex(location)->getValue();
	}

	virtual const T &getElementAt(int location) const
	{
		return getNodeAtIndex(location)->getValue();
	}

	//sets the value at the specified index
	virtual void setElementAt(T value, int location)
	{
		getNodeAtIndex(location)->setValue(value);
	}

	//adds the specified item at the specified index and shifts everything else
	//to the "right" by one.
	virtual void addElementAt(T value, int location)
	{
		ListNode<T> *new_value = createNode(value);

		//When adding to a LL, we have to consider two possibilities:
		//Option #1: are we adding this to the front?
		if (location == 0)
		{
			new_value->setNext(_front);
			_front = new_value;
		}
		else if (location == _size)
		{
			//adding to the end of the list?
			_end->setNext(new_value);
			_end = _end->getNext();
		}
		else
		{
			//Option #2: Adding somewhere else
			ListNode<T> *before = getNodeAtIndex(location - 1);
			new_value->setNext(before->getNext());
			before->setNext(new_value);
		}

		//is size 0
		if (_size == 0)
		{
			_end = _front;
		}

		//remember to increment size counter
		_size++;

	}

	//CLASS TODO
	//removes the element at the specified index.
	virtual void removeElementAt(int index)
	{
		//make sure index is in bounds
		if (index < 0 || index >= getSize())
		{
			throw out_of_range("Invalid index.");
		}

		//two possibilities:
		//Index is 0 (first item in LL)
		if (index == 0)
		{
			ListNode<T> *old_front = _front;
			_front = _front->getNext();
			delete old_front;
		}
		else
		{
			//Index is greater than 0 (not the first item in LL)
			ListNode<T> *before = getNodeAtIndex(index - 1);
			ListNode<T> *to_delete = before->getNext();
			before->setNext(to_delete->getNext());
			deleteNode(to_delete);

			//check to see if we removed the last element
			if (index == _size - 1)
			{
				_end = before;
			}
		}

		//is our size 1?
		if (_size == 1)
		{
			_end = _front;
		}

		//remember to decrement size
		_size--;
	}

#pragma endregion

};

#endif // !OLD_LINKED_LIST_H
