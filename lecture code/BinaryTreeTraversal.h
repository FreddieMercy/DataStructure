#ifndef BINARY_TREE_TRAVERSAL_H
#define BINARY_TREE_TRAVERSAL_H

#include "BinaryNode.h"

template <typename T>
class BinaryTreeTraversal
{
public:
	virtual void traverse(BinaryNode<T> *root) = 0;
};
#endif