#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "IndexedSorter.h"

template <typename T>
class BubbleSort : public IndexedSorter<T>
{
	//see http://en.wikipedia.org/wiki/Bubble_sort for a 
	//Bubble Sort implementation
	virtual Indexed<T>& sort(Indexed<T>& data)
	{
		int data_size = data.getSize();
		bool swapped = false;
		while (false == swapped)
		{
			swapped = true;
			for (int i = 1; i < data_size - 1; i++)
			{
				T prev = data.getElementAt(i - 1);
				T current = data.getElementAt(i);
				if (prev > current)
				{
					data.setElementAt(current, i - 1);
					data.setElementAt(prev, i);
					swapped = false;
				}
			}
			data_size--;
		}
		return data;
	}
};

#endif