//
// Created by raphael on 4/19/18.
//


#include <iostream>
#include "algortihms/LinearProgrammingSolver.h"
#include "utils/FileManager.h"

int main(int argc, char* argv[])
{
/*
	Tree<int> *tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->addChild("2.2");
	tree->addChild("3");
	tree->addChild("4");


	AgentTreeExplorationInstance atei = AgentTreeExplorationInstance
			(tree, 2, 4);
*/

	AgentTreeExplorationInstance atei = FileManager::readInstanceFromFile("../data/testFiles/test1.2.txt");

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(&atei);

	solver.getLp().writeMPS("mps.txt");
	solver.getLp().writeSol("sol.txt");
	solver.getLp().printSol("print.txt");

	return 0;
}