#ifndef HW2_H
#define HW2_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;


class scores
{
private:
	int overAll = 0;
	vector<int> details;
	string _name;
	int _id;

public:
	scores(int id, string name)
	{
		_name = name;
		_id = id;
	}

	scores()
	{
		_id = 0;
		_name = "None";
	}
	void setOverAll(int input)
	{
		overAll = input;
	}

	int getOverAll()
	{
		return overAll;
	}

	void setDetails(int input)
	{
		details.push_back(input);
	}

	vector<int> getDetails()
	{
		return details;
	}

};

class Student
{
private:
	int _id;
	string _name;
	scores hw;
	scores quiz;
	scores exams;

public:

	void setId(int i)
	{
		_id = i;
	}

	void setName(string s)
	{
		_name = s;
	}

	int getId()
	{
		return _id;
	}

	string getName()
	{
		return _name;
	}

}

//	friend ostream &operator<<(ostream &os, const Student &item);
//
//	//to hash custom classes, we need to provide a == override
//	bool operator==(const Student &other) const
//	{
//		if (_name == other._name)
//		{
//			return true;
//		}
//		return false;
//	}
//
//	string getName() const
//	{
//		return _name;
//	}
//
//	int getQuantity() const
//	{
//		return _quantity;
//	}
//
//	double getCost() const
//	{
//		return _cost;
//	}
//};
//
////for cout
//ostream &operator<<(ostream &os, const GroceryItem &item)
//{
//	os << setw(10) << left << item.getName() << ": $" << item.getCost() << " (qty: " << item.getQuantity() << ")";
//	return os;
//}
//
////hashing algorithm must exist in STD namespace
//namespace std {
//
//	template <>
//	struct hash<GroceryItem>
//	{
//		std::size_t operator()(const GroceryItem& item) const
//		{
//			size_t hash_val = 0;
//
//			//to hash strings using the STL
//			hash<string> str_hash{};
//
//			//for example, if we wanted to hash integers...
//			hash<int> int_hash{};
//
//			//TODO: define hashing algorithm.  Ours is pretty easy...
//		hash_val = str_hash(item.getName());
//
//			//add others as necessary
//			return hash_val;
//		}
//	};
//}
//
//
#endif