//
// Created by raphael on 4/19/18.
//


#include <iostream>
#include <sstream>
#include <string>
#include "algortihms/LinearProgrammingSolver.h"
#include "utils/FileManager.h"
#include "algortihms/TreeGenerator.h"
#include "algortihms/instanceGenrator.h"

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
	*/


	vector<int> values = {12,12,13,13,13,14,14,14,16,16,16,17,17,17,20,20,22,22};
	//vector<int> values = {12,12,14,14,17,17,17,18,18,18,20,20,20,21,21,21,22,22};

	int S = 0, k = 6;
	for(int v : values)
		S += v;

	//Tree<int> *tree = TreeGenerator::generate3PartitionTree(values);

	//AgentTreeExplorationInstance atei = AgentTreeExplorationInstance(tree, 2, 4);

	//AgentTreeExplorationInstance atei = AgentTreeExplorationInstance(tree, k, 3 * S / k);

	//AgentTreeExplorationInstance atei = FileManager::readInstanceFromFile("../data/testFiles/test1.2.txt");

	AgentTreeExplorationInstance atei = FileManager::readInstanceFromFile("../data/misc/2-3-1.txt");

	//AgentTreeExplorationInstance atei = instanceGenrator::generate3Partition(5);

	//FileManager::writeInstanceToFile("../data/3Partition/tree4.txt", &atei);

	cout << atei << endl;

	cout << "Linear Program:" << endl;

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	vector<vector<Edge<int> *>> walks = solver.solver(&atei);

	cout << endl << "Integer Linear Program On Generated Walks:" << endl;

	solver.integerSolver(&atei, walks);

	solver.printIntegerSolution();

	solver.printWalks(walks);

	cout << endl << "Optimal:" << endl;

	solver.optiSolver(&atei);


/*
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
*/
	return 0;
}