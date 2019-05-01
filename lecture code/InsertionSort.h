#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "IndexedSorter.h"

template <typename T>
class InsertionSort : public IndexedSorter<T>
{
	//Insertion Sort taken from Wikipedia: http://en.wikipedia.org/wiki/Insertion_sort
	//See site for a nice visualization of the process
	virtual Indexed<T>& sort(Indexed<T>& data)
	{
		for (int i = 1; i < data.getSize(); i++)
		{
			int j = i;
			while (j > 0 &&
				data.getElementAt(j - 1) > data.getElementAt(j)
				)
			{
				T temp = data.getElementAt(j - 1);
				T current = data.getElementAt(j);
				data.setElementAt(current, j - 1);
				data.setElementAt(temp, j);
				j--;
			}
			
		}
		return data;
	}
};

#endif