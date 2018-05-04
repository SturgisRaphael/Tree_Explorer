//
// Created by zampieri on 04/05/18.
//

#include <iostream>
#include <queue>
#include "TreeGenerator.h"

vector<Tree<int>*> TreeGenerator::generateBinaryTrees(int depth) {
	vector<Tree<int>*> result;
	int index = 0;
	Tree<int>* tree = new Tree<int>(&index, "root");
	generateCompleteBinaryTree(depth, tree);

	queue<Tree<int>*> queue;
	queue.push(tree);

	while(!queue.empty())
	{
		Tree<int> *head = queue.front();
		queue.pop();
		if(!isInList(head, result))
		{
			vector<Tree<int>*> leafs;
			head->getListLeaf(&leafs);

			for(auto t: leafs)
			{
				if(t->edgeToParent != nullptr) {
					int index = 0;
					Tree<int> *copy = t->getRoot()->copy(&index);
					Tree<int> *toRemove = copy->findChild(t->getLabel());
					Edge<int> *edgeToRemove = toRemove->edgeToParent;

					for (int i = 0; i < edgeToRemove->getParent()->edges.size(); i++) {
						if (edgeToRemove->getParent()->edges[i] == edgeToRemove) {
							edgeToRemove->getParent()->edges.erase(edgeToRemove->getParent()->edges.begin() + i);
							break;
						}
					}
					delete (edgeToRemove);
					copy->reId();
					copy->reLabel();
					queue.push(copy);
				}
			}
			result.push_back(head);
		}
	}
	
	return result;
}

void TreeGenerator::generateCompleteBinaryTree(int depth, Tree<int> *tree) {
	if(depth > 0)
	{
		Tree<int> *child1 = tree->addChild(std::to_string(*tree->index));
		Tree<int> *child2 = tree->addChild(std::to_string(*tree->index));

		generateCompleteBinaryTree(depth - 1, child1);
		generateCompleteBinaryTree(depth - 1, child2);
	}
}

bool TreeGenerator::isInList(Tree<int> *&pTree, vector<Tree<int> *> vector) {
	for(auto t: vector)
		if(*pTree == *t)
			return true;
	return false;
}

/*
void TreeGenerator::generateBinaryTrees(int depth, vector<Tree<int>*> *vector, Tree<int> *currentTree) {
	bool add = true;
	for(auto T: vector[0])
		if(T == currentTree->getRoot())
			add = false;
	if(add)
	{
		vector->push_back(currentTree->getRoot());
		cout << *currentTree->getRoot() << endl;
	}
	if(depth > 0)
	{
		int index1 = *currentTree->index;
		Tree<int> *copy1 = currentTree->getRoot()->copy(&index1);
		copy1 = copy1->findChild(currentTree->getLabel());
		Tree<int> *child1 = copy1->addChild(std::to_string(*copy1->index));

		int index2 = *copy1->index;
		Tree<int> *copy2 = copy1->getRoot()->copy(&index2);
		copy2 = copy2->findChild(copy1->getLabel());
		Tree<int> *child2 = copy2->addChild(std::to_string(*copy2->index));

		generateBinaryTrees(depth - 1, vector, child1);
		generateBinaryTrees(depth - 1, vector, child2);
	}
}
*/