#ifndef SORTER_H
#define SORTER_H

//generic sorting class
template <typename Sortable>
class Sorter
{
public:
	virtual Sortable& sort(Sortable& data) = 0;
};

#endif