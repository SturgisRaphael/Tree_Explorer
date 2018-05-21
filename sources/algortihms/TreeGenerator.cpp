//
// Created by zampieri on 04/05/18.
//

#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
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

Tree<int>* TreeGenerator::generate3PartitionTree(vector<int> values) {
	int index = 0;
	Tree<int>* result =  new Tree<int>(&index, "root");


	int k = static_cast<int>(values.size() / 3);

	if(k <= 0)
	{
		cerr << "error : k = " << k << endl;
		return result;
	}

	int S = 0;
	int i = 1;
	for(int v: values)
		S+=v;
	for(int v: values)
	{
		addBranch(v, result, i);
		i++;
	}
	for(int j = 0; j < k; j++)
	{
		addBranch(S / k, result, i + j);
	}

	return result;
}

void TreeGenerator::addBranch(int k, Tree<int> *tree, int index) {
	Tree<int> *currentNode = tree;
	for(int i = 0; i < k; i++)
	{
		std::stringstream ss;
		if(i == 0)
			ss << index;
		else
			ss << currentNode->getLabel() << ".1";

		std::string s = ss.str();
		currentNode = currentNode->addChild(s);
	}
}