//
// Created by raphael on 4/19/18.
//


#include <iostream>
#include <sstream>
#include <string>
#include "algortihms/LinearProgrammingSolver.h"
#include "utils/FileManager.h"
#include "algortihms/TreeGenerator.h"

int main(int argc, char* argv[])
{
	/*
	int index = 0;
	Tree<int> *tree = new Tree<int>(&index, "root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->addChild("2.2");
	tree->addChild("3");
	tree->addChild("4");


	AgentTreeExplorationInstance atei = AgentTreeExplorationInstance
			(tree, 2, 4);

	//AgentTreeExplorationInstance atei = FileManager::readInstanceFromFile("../data/testFiles/test1.2.txt");

	cout << "Linear Program:" << endl;

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(&atei);

	cout << "Optimal:" << endl;

	solver.optiSolver(&atei);

	*/

	vector<Tree<int>*> vector = TreeGenerator::generateBinaryTrees(3);

	unsigned long treeNumber = vector.size();
	for(Tree<int>* t: vector)
	{
		AgentTreeExplorationInstance atei =	AgentTreeExplorationInstance(t, 3, 2);
		std::stringstream ss;
		ss << "../data/binaryTrees/tree" << treeNumber << ".txt";

		std::string s = ss.str();

		FileManager::writeInstanceToFile(s, &atei);
		treeNumber--;
	}

	return 0;
}