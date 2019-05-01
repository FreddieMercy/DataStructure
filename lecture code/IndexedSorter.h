#ifndef INDEXED_SORTER_H
#define INDEXED_SORTER_H

#include "Indexed.h"
#include "Sorter.h"

template <typename T>
class IndexedSorter : public Sorter<Indexed<T>>
{
public:
	virtual Indexed<T>& sort(Indexed<T>& data) = 0;
};

#endif