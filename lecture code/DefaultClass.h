#ifndef DEFAULT_CLASS_H
#define DEFAULT_CLASS_H

//Example of explicitly defining default constructors and operator='s.
//In the real world, *EVERY* class that you develop should probably have these
//methods declared and implemented or marked private
class DefaultClass
{
private:

	//In VS2013, we have to make move operations "private" to prevent use
	/*
	DefaultClass(DefaultClass &&other)
	{

	}

	DefaultClass& operator=(DefaultClass &&other)
	{
	return *this;
	}
	*/
public:

	//AC Note: can also specify =delete, which makes that function not available.  Very
	//useful if we don't want to allow copy/move operations.
	DefaultClass() = default;
	~DefaultClass() = default;
	DefaultClass(const DefaultClass &other) = default;
	DefaultClass& operator=(const DefaultClass &other) = default;

	//DefaultClass(DefaultClass &&other) = default;  //VS 2013 doesn't allow setting default move constructor
	//must provide empty implementation instead
	DefaultClass(DefaultClass &&other)
	{
		//TODO: implement
	}

	//DefaultClass& operator=(DefaultClass &&other) = default;  //VS 2013 doesn't allow setting default move operator
	DefaultClass& operator=(DefaultClass &&other)
	{
		//TODO: implement
		return *this;
	}
};

#endif