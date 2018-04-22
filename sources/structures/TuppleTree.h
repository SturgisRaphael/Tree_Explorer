//
// Created by raphael on 4/19/18.
//

#ifndef TREE_EXPLORER_TUPPLETREE_H
#define TREE_EXPLORER_TUPPLETREE_H


#include "Tupple.h"
#include "Tree.h"

class TuppleTree: public Tree<Tupple> {
public:
	TuppleTree(const string &label, TuppleTree *parent) : Tree(label,
	                                                             parent) {}
};


#endif //TREE_EXPLORER_TUPPLETREE_H
