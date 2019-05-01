#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "Stack.h"
#include "LinkedList.h"

//note: protected inheritance can be accomplished with a protected
//variable using a has-a relationship (see SortedCollection.h)
template <typename T>
class StackList : public Stack<T>, protected LinkedList<T>
{
public:

	//maps to "push"
	virtual void addElement(T item)
	{
		push(item);
	}

	virtual bool isEmpty() const
	{
		//we can reuse our parent LinkedList's isEmpty function
		return LinkedList::isEmpty();
	}

	virtual int getSize() const
	{
		return LinkedList::getSize();
	}

	//removes the "top"-most element from the stack and returns its value
	virtual T pop()
	{
		T item = getTop();
		removeElementAt(0);
		return item;
	}

	//returns the "top"-most element in the stack.
	virtual T getTop() const
	{
		getElementAt(0);
	}

	//adds the supplied element to the "top" of the stack.
	virtual void push(T item)
	{
		addElementAt(item, 0);
	}
};

#endif