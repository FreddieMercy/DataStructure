#ifndef COLLECTION_H
#define COLLECTION_H

template <typename T>
class Collection 
{
public:

	//Note that it would probably be more efficient to pass by constant reference,
	//but for learning purposes, I'm sticking to pass by value.
	virtual void addElement(T item) = 0;
	virtual bool isEmpty() const = 0;
	virtual int getSize() const = 0;
};

#endif