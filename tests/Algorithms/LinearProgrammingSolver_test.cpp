//
// Created by raphael on 4/23/18.
//

#include <gtest/gtest.h>
#include <malloc.h>
#include "../../sources/structures/Tree.h"
#include "../../sources/structures/AgentTreeExplorationInstance.h"
#include "../../sources/algortihms/LinearProgrammingSolver.h"
#include "../../sources/structures/Tupple.h"
#include "../../sources/structures/BinaryTree.h"

TEST(LinearProgrammingSolver, loadMatrix) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");

	vector<vector<Edge<int>*>> walks = {{tree->getEdge("1")}};

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 1, 1);

	double** matrix = LinearProgrammingSolver::loadInstanceInMatrix(atei,walks);

	ASSERT_EQ(matrix[0][0], 1);
	ASSERT_EQ(matrix[0][1], 0);
	ASSERT_EQ(matrix[1][0], -1);
	ASSERT_EQ(matrix[1][1], 1);
	ASSERT_EQ(matrix[2][0], 0);
	ASSERT_EQ(matrix[2][1], 1);

	for(int i = 0; i < 2* atei->getTree()->numberOfEdges() + 1; i++)
		free(matrix[i]);
	free(matrix);

	delete atei;
}

TEST(LinearProgrammingSolver, loadMatrix2) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");

	vector<vector<Edge<int>*>> walks = {{tree->getEdge("1")}, {tree->getEdge
			("2")}};

	AgentTreeExplorationInstance *atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	double** matrix = LinearProgrammingSolver::loadInstanceInMatrix(atei,walks);

	ASSERT_EQ(matrix[0][0], 1);
	ASSERT_EQ(matrix[0][1], 1);
	ASSERT_EQ(matrix[0][2], 0);
	ASSERT_EQ(matrix[0][3], 0);

	ASSERT_EQ(matrix[1][0], -1);
	ASSERT_EQ(matrix[1][1], 0);
	ASSERT_EQ(matrix[1][2], 1);
	ASSERT_EQ(matrix[1][3], 0);

	ASSERT_EQ(matrix[2][0], 0);
	ASSERT_EQ(matrix[2][1], -1);
	ASSERT_EQ(matrix[2][2], 0);
	ASSERT_EQ(matrix[2][3], 1);

	ASSERT_EQ(matrix[3][0], 0);
	ASSERT_EQ(matrix[3][1], 0);
	ASSERT_EQ(matrix[3][2], 1);
	ASSERT_EQ(matrix[3][3], 0);

	ASSERT_EQ(matrix[4][0], 0);
	ASSERT_EQ(matrix[4][1], 0);
	ASSERT_EQ(matrix[4][2], 0);
	ASSERT_EQ(matrix[4][3], 1);

	for(int i = 0; i < 2* atei->getTree()->numberOfEdges() + 1; i++)
		free(matrix[i]);
	free(matrix);

	delete atei;
}

TEST(LinearProgrammingSolver, buildGlpkMatrices){
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");

	vector<vector<Edge<int>*>> walks = {{tree->getEdge("1")}, {tree->getEdge
			("2")}};

	AgentTreeExplorationInstance * atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	int p;
	p = static_cast<int>(walks.size());
	int m = atei->getTree()->numberOfEdges();

	int *ia;
	ia = static_cast<int *>(malloc(((p + m) * (2 * m + 1) + 1) * sizeof(int)));
	int *ja;
	ja = static_cast<int *>(malloc(((p + m) * (2 * m + 1) + 1) * sizeof(int)));
	double *ar;
	ar = static_cast<double *>(malloc(((p + m) * (2 * m + 1) + 1) * sizeof(double)));

	double **matrix = LinearProgrammingSolver::loadInstanceInMatrix(atei,
	                                                                walks);

	int index = LinearProgrammingSolver::buildGlpkMatrices(ia, ja, ar, matrix,
	                                                      p, m);

	ASSERT_EQ(index, 20);

	ASSERT_EQ(ia[1], 1);
	ASSERT_EQ(ja[1], 1);
	ASSERT_EQ(ar[1], 1.0);

	ASSERT_EQ(ia[2], 1);
	ASSERT_EQ(ja[2], 2);
	ASSERT_EQ(ar[2], 1.0);

	ASSERT_EQ(ia[5], 2);
	ASSERT_EQ(ja[5], 1);
	ASSERT_EQ(ar[5], -1.0);

	ASSERT_EQ(ia[7], 2);
	ASSERT_EQ(ja[7], 3);
	ASSERT_EQ(ar[7], 1.0);

	ASSERT_EQ(ia[10], 3);
	ASSERT_EQ(ja[10], 2);
	ASSERT_EQ(ar[10], -1.0);

	ASSERT_EQ(ia[12], 3);
	ASSERT_EQ(ja[12], 4);
	ASSERT_EQ(ar[12], 1.0);

	ASSERT_EQ(ia[15], 4);
	ASSERT_EQ(ja[15], 3);
	ASSERT_EQ(ar[15], 1.0);

	ASSERT_EQ(ia[20], 5);
	ASSERT_EQ(ja[20], 4);
	ASSERT_EQ(ar[20], 1.0);


	free(ia);
	free(ja);
	free(ar);

	delete atei;
}

TEST(LinearProgrammingSolver, glpk_solver) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(atei);

	delete atei;
}

TEST(LinearProgrammingSolver, extractBeta_i) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(atei);

	double *matrix = solver.extractBeta_i(2);

	cout << matrix[0] << endl;
	cout << matrix[1] << endl;

	free(matrix);

	delete atei;

}

TEST(LinearProgrammingSolver, makeBinaryTree) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(atei);

	double *matrix = solver.extractBeta_i(2);

	BinaryTree<Tupple> *binaryTree = solver.makeBinaryTree(tree, matrix);

	BinaryTree<Tupple<int, double>> *comp = new BinaryTree("root", Tupple<int, double>(0, 0));
	comp->addChild("1");
	comp->addChild("2");

	Tree<Tupple<int, double>> *a = comp->convert(), *b = binaryTree->convert();

	ASSERT_EQ(a, b);
	ASSERT_EQ(a->getEdge("1")->getWeight(), b->getEdge("1")->getWeight());
	ASSERT_EQ(a->getEdge("2")->getWeight(), b->getEdge("2")->getWeight());
}
