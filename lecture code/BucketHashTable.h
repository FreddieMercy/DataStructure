#ifndef BUCKET_HASH_TABLE_H
#define BUCKET_HASH_TABLE_H

#include "HashTableBase.h"
#include "HashItem.h"
#include <vector>
using namespace std;

template <typename Key, typename Value>
class BucketHashTable : public HashTableBase<Key, Value>
{
private:

	//bucket hash table uses its own data structure to hold items.  There's
	//probably a better OOP appraoch to this, but it works for instructional purposes.
	vector<HashItem<Key, vector<HashItem<Key, Value>>>> _buckets;

protected:
	//hash calculation function
	virtual int getHash(const string &item, int mod_by)
	{
		////hashing algorithm #1 (bad)
		//int hash = 0;
		//for (char ch : item)
		//{
		//	hash += ch;
		//}
		//return hash & mod_by;

		//hashing algorithm #2
		unsigned int hash = 0;
		char current_item;
		for (int i = 0; i < item.length(); i++)
		{
			current_item = item[i];
			hash += current_item * current_item;
			hash = hash << 8;
		}
		int result = hash % mod_by;
		return result;

		////Robert's hashing algorithm
		//unsigned int hash = 0;
		//hash = item.at(0) * item.at(item.size() - 1);
		//hash *= item.size();
		//return hash & mod_by;
	}

	//get hash shortcut
	virtual int getHash(const string &item)
	{
		int result = getHash(item, _buckets.size());
		return result;
	}

	//determines whether or not we need to resize
	//to turn off resize, just always return false
	virtual bool needsResize()
	{
		//based on adam's results, load factor isn't as important in buckets, so
		//we will increase to 0.85
		if (_number_of_elements > (0.85 * _primes[_local_prime_index]))
		{
			return true;
		}
		return false;
	}

	//called to check to see if we need to resize
	virtual void resizeCheck()
	{
		//Right now, resize when load factor > .75; it might be worth it to experiemnt with 
		//this value for different kinds of hashtables
		if (needsResize())
		{
			_local_prime_index++;

			BucketHashTable<Key, Value> new_hash{ _primes[_local_prime_index] };

			for (HashItem<Key, vector<HashItem<Key, Value>>> item : _buckets)
			{
				for (auto sub_item : item.getValue())
				{
					if (sub_item.isEmpty() == false)
					{
						//add to new hash table 
						new_hash.addElement(sub_item.getKey(), sub_item.getValue());
					}
				}
			}

			//AC Note: this calls copy operator.  Ideally, we want to call move operator.
			*this = move(new_hash);
		}
	}

public:

	//Default constructor
	BucketHashTable(int number_of_elements = 11)
		: HashTableBase()
	{
		_buckets = vector<HashItem<Key, vector<HashItem<Key, Value>>>>{(unsigned)number_of_elements};
		_local_prime_index = 0;
		_number_of_elements = 0;

		while (_primes[_local_prime_index] < number_of_elements)
		{
			_local_prime_index++;
		}
	}

	//copy constructor
	BucketHashTable(const BucketHashTable<Key, Value> &other)
		: HashTableBase(other)
	{
		_buckets = other._buckets;
	}

	//copy operator
	BucketHashTable & operator=(BucketHashTable<Key, Value> &other)
	{
		HashTableBase::operator=(other);
		_buckets = other._buckets;
		return *this;
	}

	//move constructor
	BucketHashTable(BucketHashTable<Key, Value> &&other)
		: HashTableBase(other)
	{
		swap(other._buckets, _buckets);
	}

	//move operator
	BucketHashTable & operator=(BucketHashTable<Key, Value> &&other)
	{
		HashTableBase::operator=(other);
		swap(other._buckets, _buckets);
		return *this;
	}

	//concrete implementation for parent's addElement method
	virtual void addElement(const Key &key, const Value &value)
	{
		//check for size restrictions
		resizeCheck();

		//calculate hash based on key
		int hash = getHash(key);

		//find the bucket
		HashItem<Key, vector<HashItem<Key, Value>>> *bucket = &_buckets[hash];

		//and then find the item in the bucket if it exists
		HashItem<Key, Value> *item = nullptr;
		for (auto bucket_item : bucket->getValue())
		{
			if (bucket_item.getKey() == key)
			{
				item = &bucket_item;
			}
		}

		//create value if none exists
		if (item == nullptr)
		{
			HashItem<Key, Value> kvp = HashItem<Key, Value>{key, value};
			kvp.setIsEmpty(false);
			bucket->getValue().push_back(kvp);
		}
		else
		{
			item->setValue(value);
		}

		//bucket cannot be empty
		bucket->setIsEmpty(false);

		//remember how many things we're presently storing
		_number_of_elements++;
	}

	//removes supplied key from hash table
	virtual void removeElement(Key key)
	{
		//calculate hash
		int hash = getHash(key);

		//find key in bucket
		HashItem<Key, vector<HashItem<Key, Value>>> *bucket = &_buckets[hash];
		bool found = false;
		for (auto item : bucket->getValue())
		{
			if (item.getKey() == key)
			{
				//lazy delete -- will actually get removed on next resize
				item.setIsEmpty(true);
				found = true;
			}
		}

		//throw exception if key not found
		if (found == false)
		{
			throw exception("Key not found.");
		}
		_number_of_elements--;
	}

	//returns true if the key is contained in the hash table
	virtual bool containsElement(Key key)
	{
		//calculate hash
		int hash = getHash(key);

		//find key in bucket
		HashItem<Key, vector<HashItem<Key, Value>>> *bucket = &_buckets[hash];
		bool found = false;
		for (auto item : bucket->getValue())
		{
			if (item.getKey() == key)
			{
				found = true;
				break;
			}
		}
		return found;
	}

	//returns the item pointed to by key
	virtual Value &getElement(string key)
	{
		//calculate hash
		int hash = getHash(key);

		//find key in bucket
		HashItem<Key, vector<HashItem<Key, Value>>> *bucket = &_buckets[hash];
		bool found = false;
		for (auto item : bucket->getValue())
		{
			if (item.getKey() == key)
			{
				return item.getValue();
			}
		}

		//throw exception if key not found
		throw exception("Key not found.");
	}
};

#endif