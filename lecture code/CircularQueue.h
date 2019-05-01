#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "Queue.h"
#include "Vector.h"

template <typename T>
class CircularQueue : public Queue<T>
{
private:
	Vector<T> *_container = nullptr;
	int _front = 0;
	int _end = 0;
	int _size = 0;

public:
	CircularQueue()
	{
		_container = new Vector < T > {};
	}

	virtual ~CircularQueue()
	{
		delete _container;
	}


#pragma region Queue Implementation

	virtual T &getFirst()
	{
		return _container->getElementAt(_front);
	}

	virtual void enqueue(T item)
	{
		//is queue full
		if (_size > 0
			&& _front == _end
			)
		{
			int old_end = _container->getSize();
			_container->setSize(old_end * 2 + 1);

			//unwind if necessary
			if (_end <= _front)
			{
				_end--;
				while (_end >= 0)
				{
					_container->setElementAt(_container->getElementAt(_end), old_end);
					_end--;
					old_end++;
				}
			}

			if (_end <= 0)
			{
				_end = old_end;
			}

		}

		//add item to queue
		_container->setElementAt(item, _end);
		_end++;
		if (_end >= _container->getSize())
		{
			_end = 0;
		}
		_size++;
	}

	virtual T dequeue()
	{
		T element = getFirst();
		_front++;
		if (_front >= _container->getSize())
		{
			_front = 0;
		}
		_size--;
		return element;
	}

#pragma endregion

#pragma region Collection Implementation

	virtual void addElement(T item)
	{
		this->enqueue(item);
	}
	virtual bool isEmpty() const
	{
		return _size == 0;
	}
	virtual int getSize() const
	{
		return _size;
	}

#pragma endregion



};

#endif