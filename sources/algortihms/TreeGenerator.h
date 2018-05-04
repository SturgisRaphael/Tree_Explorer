//
// Created by zampieri on 04/05/18.
//

#ifndef TREE_EXPLORER_TREEGENERATOR_H
#define TREE_EXPLORER_TREEGENERATOR_H


#include "../structures/Tree.h"

class TreeGenerator {
	friend class Tree<int>;
public:
	static vector<Tree<int>*> generateBinaryTrees(int depth);

private:
	static void generateCompleteBinaryTree(int depth, Tree<int> *tree);
	//static void generateBinaryTrees(int depth, vector<Tree<int>*> *vector, Tree<int> *currentTree);
	static bool isInList(Tree<int> *&pTree, vector<Tree<int> *> vector);
};


#endif //TREE_EXPLORER_TREEGENERATOR_H
