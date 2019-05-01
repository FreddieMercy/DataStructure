#ifndef STACK_H
#define STACK_H

#include "Collection.h"

//Stacks allow us to add and remove items from the "end" of our collection.
template <typename T>
class Stack : public Collection<T>
{
public:

	//removes the "top"-most element from the stack and returns its value
	virtual T pop() = 0;

	//returns the "top"-most element in the stack.
	virtual T getTop() const = 0;

	//adds the supplied element to the "top" of the stack.
	virtual void push(T item) = 0;
};

#endif