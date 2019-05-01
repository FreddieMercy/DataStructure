#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "IndexedSorter.h"

template <typename T>
class SelectionSort : public IndexedSorter<T>
{
	//see http://en.wikipedia.org/wiki/Selection_sort for a 
	//Selection Sort implementation
	virtual Indexed<T>& sort(Indexed<T>& data)
	{
		int min_index = 0;
		for (int j = 0; j < data.getSize() - 1; j++)
		{
			min_index = j;
			for (int i = j + 1; i < data.getSize(); i++)
			{
				T smallest = data.getElementAt(min_index);
				T current = data.getElementAt(i);
				if (current < smallest)
				{
					min_index = i;
				}
			} //end of find smallest index loop

			if (min_index != j)
			{
				T at_j = data.getElementAt(j);
				T at_min = data.getElementAt(min_index);
				data.setElementAt(at_min, j);
				data.setElementAt(at_j, min_index);
			}
		}
		return data;
	}
};

#endif