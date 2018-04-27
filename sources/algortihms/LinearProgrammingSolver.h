//
// Created by raphael on 4/20/18.
//

#ifndef TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H
#define TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H

#include "../structures/AgentTreeExplorationSolution.h"
#include "../glpk/glpk_interface.h"
#include "../structures/Tupple.h"
#include "../structures/Tripple.h"

class LinearProgrammingSolver {
private:
	friend class Tree<int>;
	glpk_interface lp;

	void PI_r(Tree<Tupple<int, double>> *binaryTree, int battery);
	void PI_f(Tree<Tupple<int, double>> *binaryTree, int battery);

public:
	glpk_interface &getLp();

	AgentTreeExplorationSolution solver(AgentTreeExplorationInstance *atei);

	void initializeGlpk(int p, int m, int k);
	static double** loadInstanceInMatrix(AgentTreeExplorationInstance *atei,
	                                     vector<vector<Edge<int> *>> walks);
	void loadInstanceInGlpk(AgentTreeExplorationInstance *atei,
	                               vector<vector<Edge<int>*>> walks);

	static int buildGlpkMatrices(int *ia, int *ja, double *ar, double **matrix, int p,
	                             int m);

	double *extractBeta_i(int m);

	void makeBinaryTreeRecursion(Tree<int> *tree, Tree<Tupple<int, double>> *binaryTree,
	                             double *matrix);

	Tree<Tupple<int, double>> *makeBinaryTree(Tree<int> *tree, double *matrix);

	vector<Edge<int>*> findBestWalk(Tree<int> *referenceTree, Tree<Tupple<int, double>> *binaryTree);

	void findBestWalkRecursion(Tree<Tupple<int, double>> *binaryTree);
};


#endif //TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H
