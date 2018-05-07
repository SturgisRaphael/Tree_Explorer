//
// Created by raphael on 4/20/18.
//

#ifndef TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H
#define TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H

#include "../structures/AgentTreeExplorationSolution.h"
#include "../glpk/glpk_interface.h"
#include "../structures/Tupple.h"
#include "../structures/Tripple.h"
#include <vector>

using namespace std;

class LinearProgrammingSolver {
private:
	friend class Tree<int>;
	glpk_interface lp;
	int p, m;

public:
	glpk_interface &getLp();

	vector<vector<Edge<int> *>> solver(AgentTreeExplorationInstance *atei);
	AgentTreeExplorationSolution optiSolver(AgentTreeExplorationInstance *atei);
	void integerSolver(AgentTreeExplorationInstance *atei, vector<vector<Edge<int> *>> walks);
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

	vector<Edge<int> *> findBestWalk(Tree<int> *referenceTree, Tree<Tupple<int, double>> *binaryTree, int battery);
	void findBestWalkId(Tree<Tupple<int, double>> *binaryTree, vector<int> *ids, int battery,
						bool returnToNode);

	void tmpFunc(Tree<Tupple<int, double>> *binaryTree, int battery);//TODO: remove

	void PI_r(Tree<Tupple<int, double>> *binaryTree, int battery);
	void PI_f(Tree<Tupple<int, double>> *binaryTree, int battery);

	AgentTreeExplorationSolution solver2(AgentTreeExplorationInstance *atei);

	void printSolution();

	bool isInWalks(vector<vector<Edge<int> *>> walks, vector<Edge<int> *> walk);

	void printWalks(vector<vector<Edge<int> *>> vector);

	void walkGenerator(vector<vector<Edge<int> *>> *outputVector, Edge<int> * origin, vector<Edge<int> *>currentWalk, int battery, Tree<int> *tree);

	void printWalk(vector<Edge<int> *> vector);

	void initializeGlpkInteger(int p, int m, int agents);
};

template<class T>
const double *Tree<T>::getPI_r() const {
	return PI_r;
}

template<class T>
const double *Tree<T>::getPI_f() const {
	return PI_f;
}

template<class T>
const Tupple<int, int> *Tree<T>::getPI_r_origin() const {
	return PI_r_origin;
}

template<class T>
const Tupple<int, int> *Tree<T>::getPI_f_origin() const {
	return PI_f_origin;
}

template<class T>
const Tupple<int, int> *Tree<T>::getPI_r_batterySplit() const {
	return PI_r_batterySplit;
}

template<class T>
const Tupple<int, int> *Tree<T>::getPI_f_batterySplit() const {
	return PI_f_batterySplit;
}


#endif //TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H
