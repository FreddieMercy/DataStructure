#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "Indexed.h"
#include "Vector.h"
#include "SkipNode.h"
#include "RandomNumberGenerator.h"
#include <utility>
using namespace std;

template <typename T>
class SkipList : public Collection<T>
{
private:
	Vector<SkipNode<T> *> _nodes;
	RandomNumberGenerator _rng;
	int _size = 0;

protected:

	//finds the correct location to insert a given node
	SkipNode<T> *slide(SkipNode<T> *start, const T& item)
	{
		SkipNode<T> *current = start;
		SkipNode<T> *previous = current;

		//account for starting sentinel node
		if (start->isSentinel() == true)
		{
			current = dynamic_cast<SkipNode<T> *>(current->getNext());
		}

		//use the starting node to find our correct location
		while (current != nullptr && current->getValue() < item)
		{
			//remember new insert location
			previous = current;

			//move to the next location
			current = dynamic_cast<SkipNode<T> *>(current->getNext());
		}
		return previous;
	}

	//handles the recursive bit of adding new elements to the list
	pair<SkipNode<T> *, int> addElementHelper(SkipNode<T> *start, const T& item, int depth = 0)
	{
		SkipNode<T> *insert_location = slide(start, item);
		pair<SkipNode<T> *, int> bubble_result;
		bubble_result.second = 0;

		//if we're not at the bottom, we need to call ourselves again
		if (insert_location->getBelow() != nullptr)
		{
			bubble_result = addElementHelper(insert_location->getBelow(), item, depth - 1);

			//do we add a record at this level?
			if (bubble_result.second == 1)
			{
				SkipNode<T> *new_node = new SkipNode<T>{ item };
				new_node->setNext(insert_location->getNext());
				insert_location->setNext(new_node);
				new_node->setBelow(bubble_result.first);

				//return a new bubble result for the caller
				pair<SkipNode<T> *, int> result;
				result.first = new_node;
				result.second = _rng.getInt(0, 1);
				return result;
			}
		}
		else //ELSE: we don't have a bottom pointer
		{
			//at the bottom, we always add nodes
			SkipNode<T> *new_node = new SkipNode<T>{ item };
			new_node->setNext(insert_location->getNext());
			insert_location->setNext(new_node);
			
			//do we get to bubble up?
			pair<SkipNode<T> *, int> result;
			result.first = new_node;
			result.second = _rng.getInt(0, 1);
			return result;
		}
	}

public:

	SkipList()
	{
		//add starting "empty" node
		SkipNode<T> *first = new SkipNode<T>{};
		first->setIsSentinel(true);
		_nodes.addElement(first);
	}

	virtual ~SkipList()
	{
		for (int i = 0; i < _nodes.getSize(); i++)
		{
			SkipNode<T> *current = _nodes.getElementAt(i);
			while (current != nullptr)
			{
				SkipNode<T> *next = dynamic_cast<SkipNode<T> *>(current->getNext());
				delete current;
				current = next;
			}
		}
	}

#pragma region Collection overrides

	virtual void addElement(T item)
	{
		//start add at "top" of SkipList
		pair<SkipNode<T> *, int> bubble_result = addElementHelper(_nodes.getElementAt(_nodes.getSize() - 1), item);
		
		//do we need to add a new top-level?
		if (bubble_result.second == 1)
		{
			//all starting nodes are empty nodes
			SkipNode<T> *empty_node = new SkipNode<T>{};
			empty_node->setIsSentinel(true);
			empty_node->setBelow(_nodes.getElementAt(_nodes.getSize() - 1));

			//the bubble result will get tacked onto the empty result
			SkipNode<T> *new_node = new SkipNode<T>{ item };
			empty_node->setNext(new_node);
			new_node->setBelow(bubble_result.first);

			_nodes.addElement(empty_node);
		}
		_size++;
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

	virtual T &getElementAt(int index)
	{
		ListNode<T> *start = _nodes.getElementAt(0);
		start = start->getNext();
		for (int i = 0; i < index && start != nullptr; i++)
		{
			start = start->getNext();
		}

		//error if start is null
		return start->getValue();
	}

};
#endif