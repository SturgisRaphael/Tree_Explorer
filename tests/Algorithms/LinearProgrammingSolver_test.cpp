//
// Created by raphael on 4/23/18.
//

#include <gtest/gtest.h>
#include <malloc.h>
#include "../../sources/structures/Tree.h"
#include "../../sources/structures/AgentTreeExplorationInstance.h"
#include "../../sources/algortihms/LinearProgrammingSolver.h"
#include "../../sources/structures/Tupple.h"

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

TEST(LinearProgrammingSolver, extractBeta_i2) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->addChild("3");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(atei);

	double *matrix = solver.extractBeta_i(3);

	cout << matrix[0] << endl;
	cout << matrix[1] << endl;
	cout << matrix[2] << endl;

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

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	Tree<Tupple<int, double>> *comp = new Tree<Tupple<int, double>>("root");
	comp->addChildBin("1", 0, Tupple<int, double>(1, 0), Tupple<int, double>(0, 0));
	comp->addChildBin("2", 0, Tupple<int, double>(1, 1), Tupple<int, double>(0, 0));

	ASSERT_EQ(*comp, *binaryTree);
	ASSERT_EQ(comp->getEdge("1")->getWeight(), binaryTree->getEdge("1")->getWeight());
	ASSERT_EQ(comp->getEdge("2")->getWeight(), binaryTree->getEdge("2")->getWeight());
}

TEST(LinearProgrammingSolver, makeBinaryTree2) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->addChild("3");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(atei);

	double *matrix = solver.extractBeta_i(3);

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	Tree<Tupple<int, double>> *comp = new Tree<Tupple<int, double>>("root");
	comp->addChildBin("1", 0, Tupple<int, double>(1, 0), Tupple<int, double>(0, 0));
	comp->addChildBin("2", 1, Tupple<int, double>(1, 1), Tupple<int, double>(0, 0));
	comp->addChildBin("3", 2, Tupple<int, double>(1, 1), Tupple<int, double>(0, 0));

	ASSERT_EQ(*comp, *binaryTree);

	ASSERT_EQ(comp->getEdge("1")->getWeight(), binaryTree->getEdge("1")->getWeight());
	ASSERT_EQ(comp->getChild(1)->getEdge("2")->getWeight(), binaryTree->getChild(1)->getEdge("2")->getWeight());
	ASSERT_EQ(comp->getChild(1)->getEdge("3")->getWeight(), binaryTree->getChild(1)->getEdge("3")->getWeight());

	ASSERT_EQ(comp->getEdge("1")->getId(), binaryTree->getEdge("1")->getId());
	ASSERT_EQ(comp->getChild(1)->getEdge("2")->getId(), binaryTree->getChild(1)->getEdge("2")->getId());
	ASSERT_EQ(comp->getChild(1)->getEdge("3")->getId(), binaryTree->getChild(1)->getEdge("3")->getId());
}
