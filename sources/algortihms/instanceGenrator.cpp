//
// Created by raphael on 5/9/18.
//

#include <iostream>
#include "instanceGenrator.h"
#include "TreeGenerator.h"

AgentTreeExplorationInstance instanceGenrator::generate3Partition(int k) {
	int S = 0, tmp = 0;
	vector<int> vect;

	/* initialize random seed: */
	srand (time(NULL));

	for(int i = 0; i < 3*k; i++)
	{
		tmp = rand() % (k*k) + (k*k);
		S += tmp;
		vect.push_back(tmp);
		cout << tmp << ", ";
	}

	cout << endl;

	Tree<int> *tree = TreeGenerator::generate3PartitionTree(vect);

	return AgentTreeExplorationInstance(tree, k, 2 * S / k);
}
