//
// Created by raphael on 4/19/18.
//

#ifndef TREE_EXPLORER_BINARYTREE_H
#define TREE_EXPLORER_BINARYTREE_H

#include "Tree.h"

template <class T>
class BinaryTree: public Tree<T> {
public:
	bool addChild(Tree<T> *child, T weight) override {
		if(this->getNumberOfChilds() > 2)
			return false;
		else
			return Tree<T>::addChild(child, weight);
	}
};


#endif //TREE_EXPLORER_BINARYTREE_H
