#ifndef PRE_ORDER_TRAVERSAL
#define PRE_ORDER_TRAVERSAL
#include <iostream>
#include "BinaryTreeTraversal.h"
using namespace std;
template <typename T>
class PreOrderTraversal : public BinaryTreeTraversal<T>
{
public:
	virtual void traverse(BinaryNode<T> *root)
	{
		//make sure root isn't null
		if (root == nullptr)
		{
			return;
		}

		//pre-order is Us - Left - Right
		cout << root->getValue() << " ";
		traverse(root->getLeftChild());
		traverse(root->getRightChild());
	}
};

#endif