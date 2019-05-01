#ifndef IN_ORDER_TRAVERSAL
#define IN_ORDER_TRAVERSAL

#include <iostream>
#include "BinaryTreeTraversal.h"
using namespace std;

template <typename T>
class InOrderTraversal : public BinaryTreeTraversal<T>
{
public:
	virtual void traverse(BinaryNode<T> *root)
	{
		//null node check
		if (root == nullptr)
		{
			return;
		}

		//in-order is Left - Us - Right
		traverse(root->getLeftChild());
		cout << root->getValue() << " ";
		traverse(root->getRightChild());
	}
};

#endif