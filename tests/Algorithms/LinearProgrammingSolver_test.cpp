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
	solver.solver2(atei);

	delete atei;
}

TEST(LinearProgrammingSolver, extractBeta_i) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver2(atei);

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
	solver.solver2(atei);

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
	solver.solver2(atei);

	double *matrix = solver.extractBeta_i(2);

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	Tree<Tupple<int, double>> *comp = new Tree<Tupple<int, double>>("root");
	comp->addChildBin("1", 0, Tupple<int, double>(1, 1), Tupple<int, double>(0, 0));
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
	solver.solver2(atei);

	double *matrix = solver.extractBeta_i(3);

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	Tree<Tupple<int, double>> *comp = new Tree<Tupple<int, double>>("root");
	comp->addChildBin("1", 0, Tupple<int, double>(1, 1), Tupple<int, double>(0, 0));
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

TEST(LinearProgrammingSolver, PI_r) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("1")->addChild("1.1");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver2(atei);

	double *matrix = solver.extractBeta_i(3);

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	solver.tmpFunc(binaryTree, 4);

	ASSERT_EQ(binaryTree->getPI_r()[0], 0);
	ASSERT_EQ(binaryTree->getPI_r()[1], 0);
	ASSERT_EQ(binaryTree->getPI_r()[2], 1);
	ASSERT_EQ(binaryTree->getPI_r()[3], 1);
	ASSERT_EQ(binaryTree->getPI_r()[4], 2);

	Tupple<int, int> a = Tupple<int, int>(-1,-1);
	Tupple<int, int> b = Tupple<int, int>(1,-1);
	Tupple<int, int> c = Tupple<int, int>(0,-1);
	Tupple<int, int> d = Tupple<int, int>(1,-1);
	Tupple<int, int> e = Tupple<int, int>(2,-1);

	ASSERT_EQ(binaryTree->getPI_r_origin()[0], a);
	ASSERT_EQ(binaryTree->getPI_r_origin()[1], a);
	ASSERT_EQ(binaryTree->getPI_r_origin()[2], c);
	ASSERT_EQ(binaryTree->getPI_r_origin()[3], c);
	ASSERT_EQ(binaryTree->getPI_r_origin()[4], c);

	ASSERT_EQ(binaryTree->getPI_r_batterySplit()[0], a);
	ASSERT_EQ(binaryTree->getPI_r_batterySplit()[1], a);
	ASSERT_EQ(binaryTree->getPI_r_batterySplit()[2], c);
	ASSERT_EQ(binaryTree->getPI_r_batterySplit()[3], d);
	ASSERT_EQ(binaryTree->getPI_r_batterySplit()[4], e);
}

TEST(LinearProgrammingSolver, PI_f) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("1")->addChild("1.1");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver2(atei);

	double *matrix = solver.extractBeta_i(3);

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	solver.tmpFunc(binaryTree, 4);

	ASSERT_EQ(binaryTree->getPI_f()[0], 0);
	ASSERT_EQ(binaryTree->getPI_f()[1], 1);
	ASSERT_EQ(binaryTree->getPI_f()[2], 2);
	ASSERT_EQ(binaryTree->getPI_f()[3], 2);
	ASSERT_EQ(binaryTree->getPI_f()[4], 3);

	Tupple<int, int> a = Tupple<int, int>(-1,-1);
	Tupple<int, int> b = Tupple<int, int>(1,-1);
	Tupple<int, int> c = Tupple<int, int>(1, 0);
	Tupple<int, int> d = Tupple<int, int>(0, -1);
	Tupple<int, int> e = Tupple<int, int>(1,-1);
	Tupple<int, int> f = Tupple<int, int>(2,-1);
	Tupple<int, int> g = Tupple<int, int>(0, 1);

	ASSERT_EQ(binaryTree->getPI_f_origin()[0], a);
	ASSERT_EQ(binaryTree->getPI_f_origin()[1], d);
	ASSERT_EQ(binaryTree->getPI_f_origin()[2], d);
	ASSERT_EQ(binaryTree->getPI_f_origin()[3], d);
	ASSERT_EQ(binaryTree->getPI_f_origin()[4], c);

	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[0], a);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[1], b);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[2], e);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[3], f);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[4], g);
}

TEST(LinearProgrammingSolver, findBestWalkId) {
	Tree<int> *tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("1")->addChild("1.1");

	AgentTreeExplorationInstance *atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver2(atei);

	double *matrix = solver.extractBeta_i(3);

	Tree<Tupple<int, double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	solver.tmpFunc(binaryTree, 4);

	vector<int> ids;

	solver.findBestWalkId(binaryTree, &ids, 4, false);


	ASSERT_EQ(ids[0], 1);
	ASSERT_EQ(ids[1], 1);
	ASSERT_EQ(ids[2], 0);
	ASSERT_EQ(ids[3], 2);
}

TEST(LinearProgrammingSolver, findBestWalk) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("1")->addChild("1.1");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 1);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver2(atei);

	double *matrix = solver.extractBeta_i(3);

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	vector<Edge<int> *> edges = solver.findBestWalk(tree, binaryTree, 4);


	ASSERT_EQ(edges[0]->getId(), 1);
	ASSERT_EQ(edges[1]->getId(), 1);
	ASSERT_EQ(edges[2]->getId(), 0);
	ASSERT_EQ(edges[3]->getId(), 2);
}

TEST(LinearProgrammingSolver, solver) {
	Tree<int>* tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("1")->addChild("1.1");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 2, 4);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(atei);

	delete atei;
}

TEST(Pi_f, NullTreeErrors) {
	Tree<int> *tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->addChild("2.2");
	tree->addChild("3");
	tree->addChild("4");

	AgentTreeExplorationInstance* atei = new AgentTreeExplorationInstance
			(tree, 4, 4);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver2(atei);

	double *matrix = solver.extractBeta_i(tree->numberOfEdges());

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	solver.tmpFunc(binaryTree, 4);

	Tree<Tupple<int,double>> *problem = binaryTree->getChild(1);


	ASSERT_EQ(problem->getPI_f()[2], 2);
	ASSERT_EQ(problem->getPI_f_origin()[2].getA(), 1);
	ASSERT_EQ(problem->getPI_f_origin()[2].getB(), -1);
	ASSERT_EQ(problem->getPI_f_batterySplit()[2].getA(), 1);
	ASSERT_EQ(problem->getPI_f_batterySplit()[2].getB(), -1);
}

TEST(solver, problem1) {
	Tree<int> *tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->addChild("2.2");
	tree->addChild("3");
	tree->addChild("4");


	AgentTreeExplorationInstance atei = AgentTreeExplorationInstance
			(tree, 1, 3);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(&atei);

	ASSERT_NE(solver.getLp().getColPrim(4), solver.getLp().getColPrim(5));
}

TEST(PI_f, problem1) {
	Tree<int> *tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->addChild("2.2");
	tree->addChild("3");
	tree->addChild("4");


	AgentTreeExplorationInstance atei = AgentTreeExplorationInstance
			(tree, 1, 3);


	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver2(&atei);

	double *matrix = solver.extractBeta_i(3);

	Tree<Tupple<int,double>> *binaryTree = solver.makeBinaryTree(tree, matrix);

	solver.tmpFunc(binaryTree, 3);

	ASSERT_EQ(binaryTree->getPI_f_origin()[0].getA(), -1);
	ASSERT_EQ(binaryTree->getPI_f_origin()[0].getB(), -1);
	ASSERT_EQ(binaryTree->getPI_f_origin()[1].getA(), 0);
	ASSERT_EQ(binaryTree->getPI_f_origin()[1].getB(), -1);
	ASSERT_EQ(binaryTree->getPI_f_origin()[2].getA(), -1);
	ASSERT_EQ(binaryTree->getPI_f_origin()[2].getB(), -1);
	ASSERT_EQ(binaryTree->getPI_f_origin()[3].getA(), -1);
	ASSERT_EQ(binaryTree->getPI_f_origin()[3].getB(), -1);

	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[0].getA(), -1);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[0].getB(), -1);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[1].getA(), 1);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[1].getB(), -1);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[2].getA(), 2);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[2].getB(), -1);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[3].getA(), 3);
	ASSERT_EQ(binaryTree->getPI_f_batterySplit()[3].getB(), -1);
}

TEST(solver, problem2) {
	Tree<int> *tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->addChild("2.2");
	tree->addChild("3");
	tree->addChild("4");

	AgentTreeExplorationInstance atei = AgentTreeExplorationInstance
			(tree, 1, 4);

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	solver.solver(&atei);
}

TEST(optimalSolver, generateWalks) {
	Tree<int> *tree = new Tree<int>("root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->addChild("2.2");
	tree->addChild("3");
	tree->addChild("4");

	LinearProgrammingSolver solver = LinearProgrammingSolver();
	vector<vector<Edge<int>*>> outputVector;

	vector<Edge<int> *> emptyVector;
	solver.walkGenerator(outputVector, nullptr, emptyVector, 3, tree);

	ASSERT_EQ(outputVector.size(), 10);
}