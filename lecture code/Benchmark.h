#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "Indexed.h"
#include "Stack.h"
#include "Queue.h"
#include "IndexedSorter.h"
#include "RandomNumberGenerator.h"
#include <unordered_map>
#include <string>
#include "HashTableBase.h"

#include <chrono>

using namespace chrono;
using namespace std;

class Benchmark
{
public:
	static long long benchmarkStarterCode()
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;

		start = system_clock::now();

		//PERFORM BENCHMARK HERE


		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	static long long queueBenchmark(Queue<int> &some_queue, int num_ops)
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		RandomNumberGenerator _rng{};

		start = system_clock::now();

		//PERFORM BENCHMARK HERE
		for (int i = 0; i < num_ops; i++)
		{
			int to_do = _rng.getInt(1, 3);

			//todo: perform operations
			switch (to_do)
			{
			case 1:
				if (some_queue.isEmpty() == false)
				{
					some_queue.dequeue();
				}
				break;

			default:
			case 2:
			case 3:
				some_queue.enqueue(i);
				break;
			}
		}

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	static long long stackBenchmark(Stack<int> &some_stack, int num_ops)
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		RandomNumberGenerator _rng{};
		start = system_clock::now();

		//PERFORM BENCHMARK HERE
		for (int i = 0; i < num_ops; i++)
		{
			int to_do = _rng.getInt(1, 3);

			//todo: perform operations
			switch (to_do)
			{
			case 1:
				if (some_stack.isEmpty() == false)
				{
					some_stack.pop();
				}
				break;

			default:
			case 2:
			case 3:
				some_stack.push(i);
				break;
			}
		}

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	static long long pushPopBenchmark(Stack<int> &some_stack, int num_ops)
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		RandomNumberGenerator _rng{};
		start = system_clock::now();

		//PERFORM BENCHMARK HERE
		for (int i = 0; i < num_ops; i++)
		{
			some_stack.push(i);
			some_stack.pop();
		}

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	static long long extendedPushPop(Stack<int> &some_stack, int num_ops)
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		RandomNumberGenerator _rng{};
		start = system_clock::now();

		//PERFORM BENCHMARK HERE
		for (int i = 0; i < num_ops; i++)
		{
			some_stack.push(i);
		}
		for (int i = 0; i < num_ops; i++)
		{
			some_stack.pop();
		}

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	static long long addAndRemoveTest1(Indexed<int> &items)
	{
		
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		start = system_clock::now();

		//PERFORM BENCHMARK HERE
		for (int i = 0; i < 5000; i++)
		{
			items.addElement(i);
		}

		for (int i = 0; i < 5000; i++)
		{
			items.removeElementAt(items.getSize() - 1);
		}


		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	static long long orderedInsertBenchmark(Collection<int> &data, int max_items)
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		start = system_clock::now();

		//insert data
		for (int i = 0; i < max_items; i++)
		{
			data.addElement(i);
		}

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	static long long randomInsertBenchmark(Collection<int> &data, int max_items)
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		RandomNumberGenerator rng{};
		start = system_clock::now();

		//insert data
		for (int i = 0; i < max_items; i++)
		{
			data.addElement(rng.getInt(0, 1000));
		}

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	template <typename T>
	static long long sortBenchmark(Indexed<T> &data, IndexedSorter<T> &sorter)
	{
		system_clock::time_point start;
		system_clock::time_point end;
		start = system_clock::now();

		//sort data
		sorter.sort(data);

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}

	//benchmarks a supplied hashing function.  Returns the total time to hash
	//as well as a map that shows hash distributions
	static pair<long long, unordered_map<int, int>> hashBenchmark(int num_hashes, int(*hasher)(string))
	{
		system_clock::time_point start;
		system_clock::time_point end;

		//use hashtable to count duplicate hashes
		unordered_map<int, int> hashes{};

		//prime with a bunch of strings
		vector<string> keys{};
		string key = "";
		for (int i = 0; i < num_hashes / 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				char value = (j % 27) + 65;
				string temp_key = key + value;
				keys.push_back(temp_key);
			}
			key += "A";
		}

		//with keys primed, run our benchmark
		start = system_clock::now();

		//hash each key
		for (string key : keys)
		{
			int result = hasher(key);

			//assume we have a hashtable of size 1001
			result %= num_hashes;

			//add slot if it doesn't exist
			if (hashes.find(result) == hashes.end())
			{
				hashes[result] = 0;
			}
			else
			{
				//increment hash count if it does
				++hashes[result];
			}
		}

		end = system_clock::now();
		long long time = duration_cast<milliseconds>(end - start).count();
		return pair<long long, unordered_map<int, int>>{time, hashes};
	}

	static long long hashTableBench(HashTableBase<string, int> &ht, int num_ops)
	{
		//placeholder benchmark code
		system_clock::time_point start;
		system_clock::time_point end;
		start = system_clock::now();

		//add and then retrieve various items in hash table
		for (int i = 0; i < num_ops; i++)
		{
			ht.addElement(to_string(i), i);
		}
		for (int i = 0; i < num_ops; i++)
		{
			int value = ht[to_string(i)];
		}

		end = system_clock::now();
		return duration_cast<milliseconds>(end - start).count();
	}
};
#endif