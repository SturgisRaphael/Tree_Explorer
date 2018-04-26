//
// Created by raphael on 4/20/18.
//

#include "LinearProgrammingSolver.h"
#include "../structures/BinaryTree.h"
#include "../structures/Tupple.h"

AgentTreeExplorationSolution
LinearProgrammingSolver::solver(AgentTreeExplorationInstance *atei) {

	vector<vector<Edge<int> *>> walks;

	int p = static_cast<int>(walks.size()), m = atei->getTree()
			->numberOfEdges();

	initializeGlpk(p, m, atei->getNumberOfAgents());

	loadInstanceInGlpk(atei, walks);

	lp.simplex(NULL);

	//glp_print_sol(lp.getRoot(), "test.txt");

	return AgentTreeExplorationSolution();
}

void
LinearProgrammingSolver::loadInstanceInGlpk(AgentTreeExplorationInstance *atei,
                                            vector<vector<Edge<int>*>> walks) {

	int p = static_cast<int>(walks.size()), m = atei->getTree()
			->numberOfEdges();
	int sizeOfLists = ((p + m) * ((m * 2) + 1)) + 1;

	int *ia = static_cast<int *>(malloc(sizeOfLists * sizeof(int)));
	int *ja = static_cast<int *>(malloc(sizeOfLists * sizeof(int)));
	double *ar= static_cast<double *>(malloc(sizeOfLists *sizeof(double)));

	double **matrix = loadInstanceInMatrix(atei, walks);

	int index = buildGlpkMatrices(ia, ja, ar, matrix, p, m);

	lp.loadMatrix(index, ia, ja, ar);

	free(ia);
	free(ja);
	free(ar);
}

int LinearProgrammingSolver::buildGlpkMatrices(int *ia, int *ja, double *ar,
                                              double **matrix, int p, int m){
	int index = 1;
	for(int i = 0; i < 2 * m + 1; i++)
	{
		for(int j = 0; j < m + p; j++)
		{
			//if(matrix[i][j] != 0)
			//{
				ia[index] = i + 1;
				ja[index] = j + 1;
				ar[index] = matrix[i][j];
				index++;
			//}
		}
		free(matrix[i]);
	}
	free(matrix);

	return index - 1;
}

void
LinearProgrammingSolver::initializeGlpk(int p, int m, int k) {
	lp = glpk_interface();

	lp.createProblem();
	lp.setProbName("atei");
	lp.setObjDir(glpk_interface::max);

	lp.addRows((m * 2) + 1);

	lp.setRowName(1, "alpha");
	lp.setRowBnds(1, glpk_interface::upper, 0.0, k);

	for(int i = 1; i <= m; i++)
	{
		string str = "beta" + to_string(i);
		lp.setRowName(1 + i, str.c_str());
		lp.setRowBnds(1 + i, glpk_interface::upper, 0.0, 0.0);
	}

	for(int i = 1; i <= m; i++)
	{
		string str = "gamma" + to_string(i);
		lp.setRowName(1 + m + i, str.c_str());
		lp.setRowBnds(1 + m + i, glpk_interface::upper, 0.0, 1.0);
	}

	lp.addCols(m + p);

	for(int i = 1; i <= p; i++){
		string str = "X" + to_string(i);
		lp.setColName(i, str.c_str());
		lp.setColBnds(i, glpk_interface::double_bound, 0.0, 1.0);
		lp.setObjCoef(i, 0.0);
	}

	for(int i = p + 1; i <= m + p; i++){
		string str = "y" + to_string(i);
		lp.setColName(i, str.c_str());
		lp.setColBnds(i, glpk_interface::double_bound, 0.0, 1.0);
		lp.setObjCoef(i, 1.0);
	}
}

double **
LinearProgrammingSolver::loadInstanceInMatrix(AgentTreeExplorationInstance *atei,
                                              vector<vector<Edge<int> *>> walks) {
	int p = static_cast<int>(walks.size()), m = atei->getTree()
			->numberOfEdges();
	auto **matrix = static_cast<double **>(calloc(
			2 * m + 1, sizeof(double*)));

	for(int i = 0; i < 2 * m + 1; i++)
		matrix[i] = static_cast<double *>(calloc(m + p, sizeof(double)));

	for(int j = 0; j < p; j++)
		matrix[0][j] = 1.0;

	for(int i = 0; i < m; i++)
	{
		matrix[i+1][i+p] = 1.0;//yi = 1

		matrix[i+1+m][i+p] = 1.0;//yi = 1

		for(int j = 0; j < p; j++)
		{
			for(Edge<int>* k : walks[j])
				if(k->getId() == i)
					matrix[i + 1][j] = -1;
		}
	}

	return matrix;
}

glpk_interface &LinearProgrammingSolver::getLp(){
	return lp;
}

double* LinearProgrammingSolver::extractBeta_i(int m){
	double* matrix;
	matrix = static_cast<double *>(malloc(m * sizeof(double)));

	for(int i = 0; i < m; i++)
	{
		matrix[i] = lp.getRowDual(i + 1);
	}
	return matrix;
}

Tree<Tupple<int, double>> *LinearProgrammingSolver::makeBinaryTree(Tree<int> *tree, double *matrix)
{
	Tree<Tupple<int, double>> *binaryTree = new Tree<Tupple<int, double>>(tree->getLabel());
	makeBinaryTreeRecursion(tree, binaryTree, matrix);
	return binaryTree;
}

void LinearProgrammingSolver::makeBinaryTreeRecursion(Tree<int> *tree, Tree<Tupple<int, double>> *binaryTree, double* matrix)
{
	Tupple<int, double> nullWeight = Tupple<int, double>(0, 0.0);
	if(tree->edges.size() != 0)
	{
		for(int i = 0; i < tree->edges.size(); i++)
		{
			int id = tree->edges[i]->getId();
			string label = tree->edges[i]->getChild()->getLabel();
			Tupple<int, double> tupple = Tupple<int, double>(1, matrix[id]);
			Tree<Tupple<int, double>> *child = binaryTree->addChildBin(label, id, tupple, nullWeight);
			makeBinaryTreeRecursion(tree->edges[i]->getChild(), child, matrix);
		}
	}
}