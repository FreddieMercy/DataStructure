#include <iostream>  
#include <string>   
#include <iomanip>  
#include <fstream>  
#include <vector>   
#include <stack>	 
#include <queue>	
#include <list>		
#include <sstream>
#include <set>		
#include <stdexcept> 
#include <algorithm> 
#include <unordered_map> 
#include "BinarySearchTree.h"
#include "LinearHashTable.h"
#include "QuadraticHashTable.h"
#include "DoubleHashTable.h"
#include "BucketHashTable.h"
#include "Benchmark.h"
#include "Vector.h"
#include "GroceryItem.h"
#include <array>

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


int hashing_by_freddie(string key)
{
	int hash_value;
	for (auto x : key)
	{
		hash_value += x;
	}

	return hash_value % 1001;
}

template <class T>
bool find_empty(array<T, 1001> sth, int hash_value)
{
	if (sth[hash_value].empty())
	{
		return true;
	}

	else
	{
		return false;
	}
}

template <class T>
int hash_table(string key, array<T, 1001>sth)
{
	int hash_value = hashing_by_freddie(key);
	bool check;
	do
	{
		check = find_empty(sth, hash_value);

		if (check == false)
		{
			hash_value = (hash_value + 1) % 1001;
		}

	} while (check == false);

	return hash_value;
}


int main(int argc, char *argv[])
{

	ifstream input("exams_1.csv");
	vector<string> list;
	string s;

	vector<scores> score;
	array<vector<scores>, 1001> Hash_Table;

	int hash_value;

	while (!input.eof())
	{
		getline(input, s);
		int Begin = 0;
		int End;

		while (s.find(',', Begin) != string::npos)
		{

			End = s.find(',', Begin) - Begin;

			string &str = s.substr(Begin, End);

			list.push_back(str);
			
			Begin += End + 1;
		}

		hash_value = hash_table(list[1], Hash_Table);
		//Hash_Table[hash_value].list);
	}


	input.close();

	return 0;
}












//int main(int argc, char *argv[])
//{
//	ifstream("exames_1.csv");
//	ifstream("exames_2.csv");
//	ifstream("quizzes_1.csv");
//	ifstream("quizzes_2.csv");
//	ifstream("homework_1.csv");
//	ifstream("homework_2.csv");
//	ofstream("Summmary.csv");
//	ofstream("Details.csv");
//
//	string str;
//
//
//
//
//
//    return 0;
//}


