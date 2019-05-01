#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#include <string>
#include <sstream>
#include "LinearHashTable.h"

using namespace std;

template <typename Key, typename Value>
class DoubleHashTable : public LinearHashTable<Key, Value>
{
protected:

	//double hash has a secondary hashing technique
	virtual int getNextProbe(int starting_hash, int probe_count)
	{
		int second_try = (starting_hash * (HashTableBase::getHash(to_string(probe_count)) + 2)) % _items.size();
		if (second_try == 0)
		{
			second_try++;
		}
		return second_try;
	}

	//to turn off resize, just always return false
	virtual bool needsResize()
	{
		//based on results, it looks like double hashing gets worse at about 70%
		if (_number_of_elements > (0.70 * _primes[_local_prime_index]))
		{
			return true;
		}
		return false;
	}

	virtual void resizeCheck()
	{
		//Right now, resize when load factor > .5; it might be worth it to experiemnt with 
		//this value for different kinds of hashtables
		if (needsResize())
		{
			_local_prime_index++;

			DoubleHashTable<Key, Value> new_hash{ _primes[_local_prime_index] };

			for (auto item : _items)
			{
				if (item.isEmpty() == false)
				{
					//add to new hash table 
					new_hash.addElement(item.getKey(), item.getValue());
				}
			}

			//AC Note: this calls copy operator.  Ideally, we want to call move operator.
			*this = move(new_hash);
		}
	}

public:
	DoubleHashTable(int number_of_elements = 11)
		: LinearHashTable(number_of_elements)
	{
	}

	DoubleHashTable(DoubleHashTable<Key, Value> &other)
		: HashTableBase(other)
	{

	}

	DoubleHashTable(DoubleHashTable<Key, Value> &&other)
		: HashTableBase(other)
	{

	}

	DoubleHashTable & operator=(DoubleHashTable<Key, Value> &other)
	{
		HashTableBase::operator=(other);
		return *this;
	}

	DoubleHashTable & operator=(DoubleHashTable<Key, Value> &&other)
	{
		HashTableBase::operator=(other);
		return *this;
	}
};
#endif