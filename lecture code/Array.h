#ifndef ARRAY_H
#define ARRAY_H
#include <stdexcept>
#include <exception>
#include <utility>
#include "Indexed.h"
using namespace std;

template <typename T>
class Array : public Indexed<T>
{
	//made protected in order to give access to Vector
protected:

	//_items will handle the actual storage
	//of our data items.
	T *_items;

	//used to store the maximum size of
	//our array
	int _max_size;

	//tracks the ACTUAL number of items
	//in our array
	int _number_of_items;

public:

#pragma region constructors / destructors

	//Constructor: responsible for setting maximum size and
	//dynamically allocating enough space to store everything.
	Array(const int max_size)
		: _max_size(max_size) //this is the same as line 45
	{
		//error checking
		if (max_size < 0)
		{
			//size is out of range, throw an exception
			throw out_of_range("Initial size cannot be less than zero.");
		}

		_items = new T[max_size];
		_number_of_items = 0;
		//_max_size = max_size; //same as line 34
	}

	//Copy constructor, necessary for proper assignment when dealing with dynamics
	//O(N); N = size of other array
	Array(const Array<T> &other)
		: _items(nullptr)
	{
		//O(1)
		if (this != &other)
		{
			//delete existing contents if they exit
			//O(1)
			if (_items != nullptr)
			{
				delete[] _items;
			}

			//copy over other's information
			//AC: pretty sure we don't need the +1, afraid to remove
			//O(1) (verified getSize() is O(1))
			_max_size = other.getSize() + 1;
			_number_of_items = other.getSize();
			_items = new T[_max_size];

			//O(N)
			for (int i = 0; i < _number_of_items; i++)
			{
				T item = other.getElementAt(i);
				_items[i] = item;
			}
		}
	}

	//We need to delcare a destructor because we're dynamically allocating memory
	//in our constructor
	~Array()
	{
		if (_items != nullptr)
		{
			delete[] _items;
		}
	}

#pragma endregion

	//methods that originally came from the Collection interface
#pragma region Collection overrides

	//Will return true if we have no items in our Array.  False otherwise.
	virtual bool isEmpty() const
	{
		return _number_of_items == 0;
	}

	//Returns the number of items currently in the array.  Note that
	//there still might be NULL values that exist within this range.
	virtual int getSize() const
	{
		return _number_of_items;
	}

	//adds an item to the "end" of our array
	//O(1)
	virtual void addElement(T item)
	{
		//add element to the end of our array
		addElementAt(item, _number_of_items);
	}
#pragma endregion

	//methods that originally came from the Indexed interface
#pragma region Indexed overrides

	//returns the item at the specified index
	virtual T& getElementAt(int location)
	{
		if (location < 0 || location >= _number_of_items)
		{
			throw out_of_range("Index out of range.");
		}
		return _items[location];
	}

	//const version of getElementAt
	//O(1)
	virtual const T &getElementAt(int index) const
	{
		if (index < 0 || index >= _number_of_items)
		{
			throw out_of_range("Index out of range.");
		}
		return _items[index];
	}

	//sets the item at the specified index
	//O(1)
	virtual void setElementAt(T value, int location)
	{
		if (location < 0 || location >= _max_size)
		{
			throw out_of_range("Index out of bounds.");
		}
		_items[location] = value;

		//if this index is larger than our currently tracked _number_of_items,
		//replace with specified index
		if (_number_of_items <= location)
		{
			_number_of_items = location + 1;
		}
	}

	//adds the item at the specified index and shifts all larger items
	//"right" by one
	//O(N) - N = number of items in array
	virtual void addElementAt(T value, int location)
	{
		//make sure that we're not full and that the index is within bounds
		if (location >= _max_size)
		{
			throw out_of_range("Array index out of bounds.");
		}
		if (_number_of_items == _max_size)
		{
			throw exception("Array is at max size.");
		}

		//shift every item to the right
		//worst case is location == 0
		//best case is location == number of items
		//O(N) - N = number of items in array
		for (int i = _number_of_items - 1; i >= location; i--)
		{
			setElementAt(_items[i], i + 1);
		}

		//now that we have a spot for our item, add it to our array
		setElementAt(value, location);
	}

	//removes the item at the specified index and shifts all smaller items
	//"left" by one
	//O(N) - N = size of array
	virtual void removeElementAt(int index)
	{
		//make sure that we're in bounds
		if (index < 0 || index >= _max_size)
		{
			throw out_of_range("Index out of bounds.");
		}

		//shift everything left
		//worst case: index == 0
		//best case:  index == number of items
		//O(N) - N = size of array
		for (int i = index; i < _number_of_items - 1; i++)
		{
			_items[i] = _items[i + 1];
		}

		//do the last shift if we have room
		if (_number_of_items + 1 < _max_size)
		{
			_items[_number_of_items] = _items[_number_of_items + 1];
		}

		//decrement the number of items in our array
		_number_of_items--;
	}
#pragma endregion

#pragma region Array-specific functions

	//The setSize method for Arrays won't actually change the underlying size of the array.
	//Instead, it merely readjusts the number of items being tracked in the array.
	//O(1)
	virtual void setSize(int size)
	{
		//check for exceptions!
		if (size < 0 || size > _max_size)
		{
			throw out_of_range("Invalid size.");
		}
		_number_of_items = size;
	}

#pragma endregion

#pragma region operator overloads

	//note: this should look very similar to the copy 
	//constructor when working with dynamic memory.
	//O(N)
	virtual Array<T> & operator=(const Array<T> &other)
	{
		if (this->_items != nullptr)
		{
			delete[] _items;
		}
		_items = new T[other.getSize()];
		for (int i = 0; i < other.getSize(); i++)
		{
			setElementAt(other.getElementAt(i), i);
		}

		//Kind of goofy syntax, but we need to return a reference to ourselves.  Recall that
		//"this" refers to whatever object is calling this code.  Also recall that "this"
		//is a pointer, so we have to dereference us in order to return ourselves as a 
		//reference.
		return *this;
	}

	//shortcut for getElementAt
	//O(1)
	virtual T&  operator[](int index)
	{
		return _items[index];
	}

	//O(1)
	virtual const T& operator[](int index) const
	{
		return _items[index];
	}

#pragma endregion
};

#endif