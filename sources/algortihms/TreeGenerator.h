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
	static Tree<int>* generate3PartitionTree(vector<int> values);

private:
	static void generateCompleteBinaryTree(int depth, Tree<int> *tree);
	static bool isInList(Tree<int> *&pTree, vector<Tree<int> *> vector);
	static void addBranch(int k, Tree<int> *tree, int index);
};


#endif //TREE_EXPLORER_TREEGENERATOR_H
