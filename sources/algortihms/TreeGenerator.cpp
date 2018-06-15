//
// Created by zampieri on 04/05/18.
//

#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <cmath>
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

int global = 0;

Tree<int>* TreeGenerator::generateEquiProbabelBinaryTree(int number_of_vertex, int* index, int *name) {
	if(number_of_vertex == 0)
		return nullptr;
	else if(number_of_vertex == 1)
		return new Tree<int>(index, to_string((*name)++));
	else{
		Tree<int>* root = new Tree<int>(index, to_string((*name)++));
		vector<int> catalans = catalan(number_of_vertex );
		srand(time(NULL));
        auto maximum = 0;
        for(int i = 0; i < number_of_vertex; i++)
            maximum += catalans[i] * catalans[number_of_vertex - 1 - i];

        int random = (int)rand() % maximum;
		int cumul = 0;
		for(int i = 0; i < number_of_vertex; i++) {
			cumul += catalans[i] * catalans[number_of_vertex - 1 - i];
			if (random <= cumul) {
			    if(i > 0)
				    root->addChild(generateEquiProbabelBinaryTree(i, index, name), index);
			    if(number_of_vertex - i - 1> 0)
					root->addChild(generateEquiProbabelBinaryTree(number_of_vertex - i - 1, index, name), index);
				break;
			}
		}
		return root;
	}
}

vector<int> TreeGenerator::catalan(int vertex) {
	vector<int> catalans = {1,1};
	for(int i = 2; i <= vertex; i++)
	{
        int sum = 0;
        for(int j = 0; j < i; j++)
            sum += catalans[j] * catalans[i - 1 - j];

		catalans.push_back(sum);
	}
	return catalans;
}

Tree<int> *TreeGenerator::generateRandomTree(int number_of_vertex) {
	vector<long> randoms;
	int random;
	random = static_cast<int>(pow(number_of_vertex, 4));
	for(int i = 0; i < number_of_vertex; i++)
	{
		randoms.push_back(rand()%random);
	}
	int index = 0, name = 0;
	Tree<int> * root = new Tree<int>(&index, to_string(name++));
	root->setValue(randoms[0]);
	for(int i = 1; i < randoms.size(); i++)
		root->addChildBinSearchTree(randoms[i], &index, &name);

    return root;
}

