//
// Created by raphael on 4/25/18.
//

#ifndef TREE_EXPLORER_BINARYTREE_H
#define TREE_EXPLORER_BINARYTREE_H

#include <ostream>
#include "Tree.h"
#include <string>

using namespace std;

template <class T>
class BinaryTree : Tree<T>{
private:
	T nullEdgeValue = NULL;
	void addEdge(Edge<T> *edge){
		Tree<T>::edges.push_back(edge);
	}
public:
	BinaryTree(T nullEdge) : nullEdgeValue(nullEdge) {}

	BinaryTree(const string &label, T nullEdge) : Tree<T>(label),
	                                              nullEdgeValue(nullEdge) {}

	BinaryTree(const string &label, Edge<T> *edgeToParent, T nullEdge) : Tree<T>(
			label, edgeToParent), nullEdgeValue(nullEdge) {}

	void setNullEdge(T nullEdge) {
		BinaryTree::nullEdgeValue = nullEdge;
	}




public:

	bool operator==(const BinaryTree &rhs) const {
		return static_cast<const Tree<T> &>(*this) ==
		       static_cast<const Tree<T> &>(rhs);
	}

	bool operator!=(const BinaryTree &rhs) const {
		return !(rhs == *this);
	}

	friend ostream &operator<<(ostream &os, const BinaryTree &tree) {
		os << static_cast<const Tree<T> &>(tree);
		return os;
	}
};


#endif //TREE_EXPLORER_BINARYTREE_H
