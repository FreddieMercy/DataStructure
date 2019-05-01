#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

//our vector implements all of the functionality specified by the Indexed and Stack ADTs
#include "Array.h"
#include "Stack.h"
using namespace std;

//Our vector, like the C++ vector have both Indexed and Stack functionality.  It is the first example of 
//multiple inheritance that we've seen in class.
template <typename T>
class Vector : public Array<T>, public Stack<T>
{

private:

#pragma region private vector resize operations

	//readjusts the vector to a new size
	void adjustSize(int new_size)
	{
		//is the new size within bounds?
		if (new_size < 0)
		{
			throw out_of_range("new_size is less than zero.");
		}

		//define variables
		int i = 0;

		//note that C++ doesn't have a realloc function so we have to do this the long way
		T *new_array = new T[new_size];

		//take the smaller of the two vector sizes, used
		//for the loop below
		int smaller_size = (new_size < _number_of_items)
			? new_size          //if new_size is smaller
			: _number_of_items; //if our size is smaller

		//copy contents into new container
		for (i = 0; i < smaller_size; i++)
		{
			new_array[i] = _items[i];
		}

		//delete old container using C++ delete
		delete[] _items;

		//reassign values to new vector
		_items = new_array;
		_number_of_items = smaller_size;
		_max_size = new_size;
	}

#pragma endregion

protected:

#pragma region protected vector resize operations

	//Call this method to determine if the Vector needs to be resized
	void checkCapacity(int requested_size)
	{
		//is our array too small?
		if (requested_size >= _max_size)
		{
			//find a value of max_size that will
			//be large enough to accommodate 
			//our requested size
			int new_size = _max_size;

			//find a value that is at least twice as large as what we currently have
			while (requested_size >= new_size)
			{
				//Doubling the size of the vector is usually a pretty good bet
				new_size = (new_size * 2) + 1;
			}

			//call the actual adjust method
			adjustSize(new_size);
		}
	}

#pragma endregion
public:

#pragma region constructors / destructors

	Vector(int initial_size = 0) : Array(initial_size)
	{
	}

	//creating our own copy constructor prevents runtime exceptions.  Note that 
	//C++ makes us declare the other vector as const in order to guarantee that we
	//wont change its contents
	Vector(const Vector<T> &other)
		: Vector(other.getSize())
	{
		//copy over all elements from the other vector
		for (int i = 0; i < other.getSize(); i++)
		{
			this->setElementAt(other.getElementAt(i), i);
		}
	}

#pragma endregion

	//needed because we also inherit from Stack<T>
#pragma region Collection overrides

	//Will return true if we have no items in our Array.  False otherwise.
	virtual bool isEmpty() const
	{
		return Array::isEmpty();
	}

	//Returns the number of items currently in the array.  Note that
	//there still might be NULL values that exist within this range.
	virtual int getSize() const
	{
		return Array::getSize();
	}
#pragma endregion

#pragma region Array overrides

	//For Vector, we'll make this work just like push()
	virtual void addElement(T item)
	{
		//check capacity before adding item to the vector
		checkCapacity(_number_of_items + 1);
		push(item);
	}

	//sets  a value at the given location
	virtual void setElementAt(T value, int location)
	{
		//check our capacity, then call our parent's version of set
		checkCapacity(location);
		Array::setElementAt(value, location);
	}

	//Adds a value at the given location.  Will shift all other
	//values to the right by 1
	virtual void addElementAt(T value, int location)
	{
		//check our capacity, then call our parent's version of add

		//first, check to see if location is within bounds
		checkCapacity(location);

		//next, check to make sure that we have enough room at the end
		//of the array for the add.
		checkCapacity(_number_of_items + 1);

		//add item
		Array::addElementAt(value, location);
	}

	//Array's setSize method doesn't actually do any resizing.  The Vector-based
	//version actually will.
	virtual void setSize(int size)
	{
		checkCapacity(size);
		Array::setSize(size);
	}

#pragma endregion

#pragma region Stack overrides

	//adds a new item to the end of the vector
	virtual void push(T value)
	{
		this->setElementAt(value, _number_of_items);
	}

	//returns the "top"-most element in the stack.
	virtual T getTop() const
	{
		return getElementAt(_number_of_items - 1);
	}

	//removes an item from the end of the vector and returns the value to the caller
	virtual T pop()
	{
		T last_value = getElementAt(_number_of_items - 1);
		_number_of_items--;
		return last_value;
	}

#pragma endregion

#pragma region operator overloads

	//In the case of a vector, we'll assume that an add is telling us to add everything
	//from the other vector with ourselves
	Vector<T> operator+(const Vector<T> &other)
	{
		Vector<T> target{};

		//add us
		for (int i = 0; i < getSize(); i++)
		{
			target.push(getItem(i));
		}

		//add other
		for (int i = 0; i < other.getSize(); i++)
		{
			target.push(other.getItem(i));
		}

		//return the combined vector
		return target;
	}
#pragma endregion

};

#endif