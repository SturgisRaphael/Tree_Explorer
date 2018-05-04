//
// Created by raphael on 4/23/18.
//

#ifndef TREE_EXPLORER_EDGE_H
#define TREE_EXPLORER_EDGE_H


#include "Tree.h"

template <class T>
class Tree;

template <class T>
class Edge {
private:
	Tree<T>* parent = nullptr;
	Tree<T>* child = nullptr;
	long id = 0;
	T weight = NULL;
public:

	Edge() {}

	Edge(long id) : id(id) {}

	Edge(Tree<T> *parent, Tree<T> *child ,int index) : parent(parent), child(child) {
		id = index;
	}

	Edge(Tree<T> *parent, Tree<T> *child, long id, T weight) : parent(parent),
	                                                          child(child),
	                                                          id(id),
	                                                          weight(weight) {}

	Tree<T> *getParent() const {
		return parent;
	}

	Tree<T> *getChild() const {
		return child;
	}

	int getId() const {
		return id;
	}

	T getWeight() const {
		return weight;
	}

	void setParent(Tree<T> *parent) {
		Edge::parent = parent;
	}

	void setId(long id) {
		Edge::id = id;
	}

	virtual ~Edge() {
		delete child;
	}
};


#endif //TREE_EXPLORER_EDGE_H
