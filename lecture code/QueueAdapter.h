#ifndef QUEUE_ADAPTOR_H
#define QUEUE_ADAPTOR_H
#include "Queue.h"
#include "Indexed.h"

template <typename T>
class QueueAdapter : public Queue<T>
{
private:
	Indexed<T> *_container;

public:
	QueueAdapter(Indexed<T> *container)
	{
		_container = container;
	}

	virtual ~QueueAdapter()
	{
		delete _container;
	}

#pragma region Queue Implementation

	virtual T &getFirst()
	{
		return _container->getElementAt(0);
	}

	//adds a new item to the queue
	virtual void enqueue(T item)
	{
		//add at the very end of our container
		_container->addElementAt(item, getSize());
	}

	//removes a person from the queue
	virtual T dequeue()
	{
		T to_return = _container->getElementAt(0);
		_container->removeElementAt(0);
		return to_return;
	}

#pragma endregion

#pragma region Collection Implementation

	virtual void addElement(T item)
	{
		this->enqueue(item);
	}
	virtual bool isEmpty() const
	{
		return _container->isEmpty();
	}
	virtual int getSize() const
	{
		return _container->getSize();
	}

#pragma endregion

};

#endif