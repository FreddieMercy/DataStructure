#ifndef QUADRATIC_HASH_TABLE_H
#define QUADRATIC_HASH_TABLE_H
#include "LinearHashTable.h"
template <typename Key, typename Value>
class QuadraticHashTable : public LinearHashTable<Key, Value>
{
protected:

	//difference between linear and quadratic hash table is how they probe!
	virtual int getNextProbe(int starting_hash, int probe_count)
	{
		int next_hash = (probe_count * (1 + starting_hash * starting_hash)) % _items.size();
		return next_hash;
	}

	//to turn off resize, just always return false
	virtual bool needsResize()
	{
		//according to Weiss, quadratic hash tables should be no more than half full
		if (_number_of_elements > (0.50 * _primes[_local_prime_index]))
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

			QuadraticHashTable<Key, Value> new_hash{ _primes[_local_prime_index] };

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
	QuadraticHashTable(int number_of_elements = 11)
		: LinearHashTable(number_of_elements)
	{
	}

	QuadraticHashTable(QuadraticHashTable<Key, Value> &other)
		: HashTableBase(other)
	{

	}

	QuadraticHashTable(QuadraticHashTable<Key, Value> &&other)
		: HashTableBase(other)
	{

	}

	QuadraticHashTable & operator=(QuadraticHashTable<Key, Value> &other)
	{
		HashTableBase::operator=(other);
		return *this;
	}

	QuadraticHashTable & operator=(QuadraticHashTable<Key, Value> &&other)
	{
		HashTableBase::operator=(other);
		return *this;
	}
};

#endif