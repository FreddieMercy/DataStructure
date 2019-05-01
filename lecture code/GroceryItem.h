#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class GroceryItem
{
private:
	string _name;
	int _quantity;
	double _cost;

public:

	GroceryItem(string name = "", int quantity = 0, double cost = 0.0)
	{
		_name = name;
		_quantity = quantity;
		_cost = cost;
	}

	//must make operator<< a friend
	friend ostream &operator<<(ostream &os, const GroceryItem &item);

	//to hash custom classes, we need to provide a == override
	bool operator==(const GroceryItem &other) const
	{
		if (_name == other._name)
		{
			return true;
		}
		return false;
	}

	string getName() const
	{
		return _name;
	}

	int getQuantity() const
	{
		return _quantity;
	}

	double getCost() const
	{
		return _cost;
	}
};

//for cout
ostream &operator<<(ostream &os, const GroceryItem &item)
{
	os << setw(10) << left << item.getName() << ": $" << item.getCost() << " (qty: " << item.getQuantity() << ")";
	return os;
}

//hashing algorithm must exist in STD namespace
namespace std {

	template <>
	struct hash<GroceryItem>
	{
		std::size_t operator()(const GroceryItem& item) const
		{
			size_t hash_val = 0;
			
			//to hash strings using the STL
			hash<string> str_hash{};

			//for example, if we wanted to hash integers...
			hash<int> int_hash{};

			//TODO: define hashing algorithm.  Ours is pretty easy...
			hash_val = str_hash(item.getName());

			//add others as necessary
			return hash_val;
		}
	};
}

#endif