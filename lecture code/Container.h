/*CptS 223 */
#ifndef CONTAINER_H
#define CONTAINER_H
#include <initializer_list>
using namespace std;
class Container
{
private:
	int *_value = nullptr;

public:

	//default constructor
	Container()
	{
		_value = new int;
	}

	//constructor with a value
	Container(int starting_value)
		: Container() //automatically call default constructor
	{
		setValue(starting_value);
	}

	//constructor with initializer list
	Container(initializer_list<int> values)
		: Container()
	{
		
		//old way to get the iterator
		//initializer_list<int>::iterator iter = values.begin();
		int value = 0;
		for (auto iter = values.begin(); iter != values.end(); ++iter)
		{
			//dereferencing converts the iterator into a value
			value += *iter;
		}
		setValue(value);
	}

	//make destructor virtual to account for inheritance
	virtual ~Container()
	{
		if (_value != nullptr)
		{
			delete _value;
		}
	}

	//any time you work with dynamic memory, you need the following:
	Container(const Container &other)
		: Container() //assumption: we don't have a valid _value
					  //pointer, so we need to create one.
	{
		//make perfect copies of other
		this->setValue(other.getValue());
	}

	Container &operator=(const Container &other)
	{
		setValue(other.getValue());
		return *this;
	}

	//move constructor
	Container(Container &&other)
		: Container() //remember, assumption is that we don't have
					  //a valid state
	{
		_value = other._value;
		other._value = nullptr;
	}

	Container &operator=(Container &&other)
	{
		//assumption: we already have a valid state
		//delete our state first
		if (_value != nullptr)
		{
			delete _value;
		}
		_value = other._value;
		other._value = nullptr;
		return *this;
	}


	int getValue() const
	{
		return *_value;
	}

	void setValue(int some_value)
	{
		*_value = some_value;
	}

};

#endif