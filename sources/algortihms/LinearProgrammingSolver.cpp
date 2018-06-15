//
// Created by raphael on 4/20/18.
//

#include <iostream>
#include "LinearProgrammingSolver.h"
#include "../structures/Tupple.h"
#include "../structures/Tripple.h"
#include "../structures/Edge.h"

#define LIMIT 10000

AgentTreeExplorationSolution
LinearProgrammingSolver::solver(AgentTreeExplorationInstance *atei, double *frac) {

	vector<vector<Edge<int> *>> walks;

	vector<Edge<int> *> newWalk;

	int counter = 0;

	double* matrix;
	double old = -1.0;

	while(counter < LIMIT ){
		counter++;

		lp.housekeeping();

		int p = static_cast<int>(walks.size()), m = atei->getTree()
				->numberOfEdges();

		initializeGlpk(p, m, atei->getNumberOfAgents());

		loadInstanceInGlpk(atei, walks);

		glp_write_lp(lp.getRoot(), nullptr, "test.txt");

		lp.simplex(nullptr);

		glp_print_sol(lp.getRoot(), "test2.txt");

		matrix = extractBeta_i(m);

		Tree<Tupple<int, double>> *binaryTree = makeBinaryTree(atei->getTree(), matrix);

		double bestSumBeta_i = 0;
		newWalk = findBestWalk(atei->getTree(), binaryTree, atei->getStartingBattery(), &bestSumBeta_i);

		delete binaryTree;

		/*cout << "Beta : ";
		for(int i = 0; i < m; i++)
			cout << matrix[i] << ", ";
		cout << "alpha : "  << lp.getRowDual(1) << endl;
		cout << "gamma : ";
		for(int i = 0; i < m; i++)
			cout << lp.getRowDual(m + 2 + i) << " ";
		cout << endl;
		cout << "best beta : " << bestSumBeta_i << endl;

		printSolution();

		printWalk(newWalk);*/

		char filename[128];
		sprintf(filename, "out%d.txt", counter);

		glp_write_lp(lp.getRoot(), nullptr, filename);

		//cout << endl << "----------------------------------" << endl;

		//walks.push_back(newWalk);


		double count = 0;
		for(int i = 0; i < m; i++)
			count += matrix[i];

		free(matrix);

		if(bestSumBeta_i < lp.getRowDual(1) + 0.00001)
			break;

//		if(!isInWalks(walks, newWalk))
//		{
			walks.push_back(newWalk);
//		} else
//		{
//			cout << "error!" << endl;
//			break;
//		}
	}

	if(frac != nullptr)
		*frac = lp.getObjVal();


//	printSolution();
//
//	printWalks(walks);

	for(int i = 0; i < m; i++)
	{
		weight.push_back(0.0);
	}

	vector<double> proba;
	for(int i = 1; i <= p; i++)
	{
		auto tmp = lp.getColPrim(i);
		proba.push_back(tmp);

		for(auto edge: walks[i - 1])
		{
			weight[edge->getId()] += tmp;
		}
	}

	vector<vector<Edge<int> *>> solution =
			selectAleat(walks, proba, atei->getNumberOfAgents());

//	cout << "solution" << endl;
//	for (const auto &i : solution) {
//		printWalk(i);
//		cout << endl;
//	}


	//cout << endl;
	AgentTreeExplorationSolution result = AgentTreeExplorationSolution(solution);
	return result;
}
/*
AgentTreeExplorationSolution
LinearProgrammingSolver::optiSolver(AgentTreeExplorationInstance *atei) {

	optiSolverRecursion

	return AgentTreeExplorationSolution();
}
*/
AgentTreeExplorationSolution
LinearProgrammingSolver::solver2(AgentTreeExplorationInstance *atei) {

	vector<vector<Edge<int> *>> walks;


	int p = static_cast<int>(walks.size()), m = atei->getTree()
			->numberOfEdges();

	initializeGlpk(p, m, atei->getNumberOfAgents());

	loadInstanceInGlpk(atei, walks);

	lp.simplex(nullptr);


	//glp_print_sol(lp.getRoot(), "test.txt");

	return AgentTreeExplorationSolution();
}

void
LinearProgrammingSolver::loadInstanceInGlpk(AgentTreeExplorationInstance *atei,
                                            vector<vector<Edge<int>*>> walks) {

	int p = static_cast<int>(walks.size()), m = atei->getTree()
			->numberOfEdges();
	int sizeOfLists = ((p + m) * ((m * 2) + 1)) + 1;

	auto *ia = static_cast<int *>(malloc(sizeOfLists * sizeof(int)));
	auto *ja = static_cast<int *>(malloc(sizeOfLists * sizeof(int)));
	auto *ar= static_cast<double *>(malloc(sizeOfLists *sizeof(double)));

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
				//cout << "|" << matrix[i][j] << "|";
			//}
		}
		//cout << endl;
		free(matrix[i]);
	}
	free(matrix);

	return index - 1;
}

void
LinearProgrammingSolver::initializeGlpk(int p, int m, int k) {
	lp = glpk_interface();

	this->p = p;
	this->m = m;

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
		lp.setColBnds(i, glpk_interface::lower, 0.0, 0.0);
		lp.setObjCoef(i, 0.0);
	}

	for(int i = p + 1; i <= m + p; i++){
		string str = "y" + to_string(i - p);
		lp.setColName(i, str.c_str());
		lp.setColBnds(i, glpk_interface::lower, 0.0, 0.0);
		lp.setObjCoef(i, 1.0);
	}
}

double **
LinearProgrammingSolver::loadInstanceInMatrix(AgentTreeExplorationInstance *atei,
                                              vector<vector<Edge<int> *>> walks) {
	int p = static_cast<int>(walks.size()), m = atei->getTree()
			->numberOfEdges();
	auto **matrix = static_cast<double **>(calloc(
			static_cast<size_t>(2 * m + 1), sizeof(double*)));

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
			//cout << matrix[i][j] << "|";
		}
		//cout << endl;
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
		matrix[i] = lp.getRowDual(i + 2);
	}
	return matrix;
}

Tree<Tupple<int, double>> *LinearProgrammingSolver::makeBinaryTree(Tree<int> *tree, double *matrix)
{
	int index = 0;
	auto *binaryTree = new Tree<Tupple<int, double>>(&index, tree->getLabel());
	makeBinaryTreeRecursion(tree, binaryTree, matrix);
	return binaryTree;
}

void LinearProgrammingSolver::makeBinaryTreeRecursion(Tree<int> *tree, Tree<Tupple<int, double>> *binaryTree, double* matrix)
{
	Tupple<int, double> nullWeight = Tupple<int, double>(0, 0.0);
	if(!tree->edges.empty())
	{
		for (auto &edge : tree->edges) {
			long id = edge->getId();
			string label = edge->getChild()->getLabel();
			Tupple<int, double> tupple = Tupple<int, double>(1, matrix[id]);
			Tree<Tupple<int, double>> *child = binaryTree->addChildBin(label, id, tupple, nullWeight);
			makeBinaryTreeRecursion(edge->getChild(), child, matrix);
		}
	}
}

vector<Edge<int> *>
LinearProgrammingSolver::findBestWalk(Tree<int> *referenceTree, Tree<Tupple<int, double>> *binaryTree, int battery, double *pInt) {
	vector<int> ids;
	vector<Edge<int> *> result;
	Tree<int> *currentNode = referenceTree;

	tmpFunc(binaryTree, battery);

	findBestWalkId(binaryTree, &ids, battery, false);

	*pInt = binaryTree->getPI_f()[battery];
	for (int id : ids) {
		if(id != -1)
		{
			Edge<int> *edge = currentNode->getEdge(id);
			if(edge != nullptr)
			{
				result.push_back(edge);
				currentNode = edge->getChild();
			} else if(currentNode->getEdgeToParent()->getId() == id)
			{
				result.push_back(currentNode->edgeToParent);
				currentNode = currentNode->edgeToParent->getParent();
			}
		}
	}

	return result;
}

void LinearProgrammingSolver::PI_r(Tree<Tupple<int, double>> *binaryTree, int battery) {

	if(binaryTree->edges.empty())
	{
		binaryTree->PI_r[battery] = 0.0;
		binaryTree->PI_r_origin[battery] = Tupple<int, int>(-1,-1);
		binaryTree->PI_r_batterySplit[battery] = Tupple<int, int>(-1,-1);
	}
	else if(battery < 2)
	{
		binaryTree->PI_r[battery] = 0.0;
		binaryTree->PI_r_origin[battery] = Tupple<int, int>(-1,-1);
		binaryTree->PI_r_batterySplit[battery] = Tupple<int, int>(-1,-1);
	}
	else if(binaryTree->edges.size() == 1)
	{
		double beta = binaryTree->edges[0]->getWeight().getB();
		int w = binaryTree->edges[0]->getWeight().getA();

		binaryTree->PI_r[battery] = beta + binaryTree->edges[0]->getChild()->PI_r[battery - 2*w];
		binaryTree->PI_r_origin[battery] = Tupple<int, int>(binaryTree->edges[0]->getId(),-1);
		binaryTree->PI_r_batterySplit[battery] = Tupple<int, int>(battery - 2*w,-1);
	} else
	{
		double beta1 = binaryTree->edges[0]->getWeight().getB();
		double beta2 = binaryTree->edges[1]->getWeight().getB();

		int w1 = binaryTree->edges[0]->getWeight().getA();
		int w2 = binaryTree->edges[1]->getWeight().getA();

		double max = beta1 + binaryTree->edges[0]->getChild()->PI_r[battery-2*w1];
		Tupple<int, int> maxOrigin = Tupple<int, int>(binaryTree->edges[0]->getId(), -1);
		Tupple<int, int> maxBatterySplit = Tupple<int, int>(battery-2*w1, -1);

		int bat = battery - 2*w1 - 2*w2;

		for(int b = 0; b <= bat; b++)
		{
			if(max < beta1 + binaryTree->edges[0]->getChild()->PI_r[bat - b] + beta2 + binaryTree->edges[1]->getChild()->PI_r[b])
			{
				max = beta1 + binaryTree->edges[0]->getChild()->PI_r[bat - b] + beta2 + binaryTree->edges[1]->getChild()->PI_r[b];

				maxOrigin = Tupple<int, int>(binaryTree->edges[0]->getId(), binaryTree->edges[1]->getId());
				maxBatterySplit = Tupple<int, int>(bat - b, b);
			}
		}

		if(max < beta2 + binaryTree->edges[1]->getChild()->PI_r[battery-2*w2])
		{
			max = beta2 + binaryTree->edges[1]->getChild()->PI_r[battery-2*w2];
			maxOrigin = Tupple<int, int>(binaryTree->edges[1]->getId(), -1);
			maxBatterySplit = Tupple<int, int>(battery-2*w2, -1);
		}

		binaryTree->PI_r[battery] = max;
		binaryTree->PI_r_origin[battery] = maxOrigin;
		binaryTree->PI_r_batterySplit[battery] = maxBatterySplit;
	}
}

void LinearProgrammingSolver::PI_f(Tree<Tupple<int, double>> *binaryTree, int battery) {
	if(binaryTree->edges.empty() || battery == 0)
	{
		binaryTree->PI_f[battery] = 0.0;
		binaryTree->PI_f_origin[battery] = Tupple<int, int>(-1,-1);
		binaryTree->PI_f_batterySplit[battery] = Tupple<int, int>(-1,-1);
	}
	else if(battery == 1)
	{
		double beta1 = binaryTree->edges[0]->getWeight().getB();
		double beta2 = 0;
		if(binaryTree->edges.size() != 1)
			beta2 = binaryTree->edges[1]->getWeight().getB();
		if(beta1 < beta2)
		{
			binaryTree->PI_f[battery] = beta2;
			binaryTree->PI_f_origin[battery] = Tupple<int, int>(binaryTree->edges[1]->getId(),-1);
			binaryTree->PI_f_batterySplit[battery] = Tupple<int, int>(1-binaryTree->edges[0]->getWeight().getA(),-1);
		}
		else
		{
			binaryTree->PI_f[battery] = beta1;
			binaryTree->PI_f_origin[battery] = Tupple<int, int>(binaryTree->edges[0]->getId(),-1);
			binaryTree->PI_f_batterySplit[battery] = Tupple<int, int>(1-binaryTree->edges[0]->getWeight().getB(),-1);
		}
	}
	else if(binaryTree->edges.size() == 1)
	{
		double beta = binaryTree->edges[0]->getWeight().getB();
		int w = binaryTree->edges[0]->getWeight().getA();

		binaryTree->PI_f[battery] = beta + binaryTree->edges[0]->getChild()->PI_f[battery - w];

		binaryTree->PI_f_origin[battery] = Tupple<int, int>(binaryTree->edges[0]->getId(),-1);
		binaryTree->PI_f_batterySplit[battery] = Tupple<int, int>(battery - w,-1);
	}

	else
	{
		double beta1 = binaryTree->edges[0]->getWeight().getB();
		double beta2 = binaryTree->edges[1]->getWeight().getB();

		int w1 = binaryTree->edges[0]->getWeight().getA();
		int w2 = binaryTree->edges[1]->getWeight().getA();

		double max = beta1 + binaryTree->edges[0]->getChild()->PI_f[battery-w1];
		Tupple<int, int> maxOrigin = Tupple<int, int>(binaryTree->edges[0]->getId(), -1);
		Tupple<int, int> maxBatterySplit = Tupple<int, int>(battery-w1, -1);

		int bat = battery - 2*w1 - w2;

		for(int b = 0; b <= bat; b++)
		{
			if(max < beta1 + binaryTree->edges[0]->getChild()->PI_r[bat - b] + beta2 + binaryTree->edges[1]->getChild()->PI_f[b])
			{
				max = beta1 + binaryTree->edges[0]->getChild()->PI_r[bat - b] + beta2 + binaryTree->edges[1]->getChild()->PI_f[b];
				maxOrigin = Tupple<int, int>(binaryTree->edges[0]->getId(), binaryTree->edges[1]->getId());
				maxBatterySplit = Tupple<int, int>(bat - b, b);
			}

		}

		bat = battery - 2*w2 - w1;

		for(int b = 0; b <= bat; b++)
		{
			if(max < beta1 + binaryTree->edges[0]->getChild()->PI_f[bat - b] + beta2 + binaryTree->edges[1]->getChild()->PI_r[b])
			{
				max = beta1 + binaryTree->edges[0]->getChild()->PI_f[bat - b] + beta2 + binaryTree->edges[1]->getChild()->PI_r[b];
				maxOrigin = Tupple<int, int>(binaryTree->edges[1]->getId(), binaryTree->edges[0]->getId());
				maxBatterySplit = Tupple<int, int>(b, bat - b);
			}
		}

		if(max < beta2 + binaryTree->edges[1]->getChild()->PI_f[battery-w2])
		{
			max = beta2 + binaryTree->edges[1]->getChild()->PI_f[battery-w2];
			maxOrigin = Tupple<int, int>(binaryTree->edges[1]->getId(), -1);
			maxBatterySplit = Tupple<int, int>(battery-w2, -1);
		}

		binaryTree->PI_f[battery] = max;
		binaryTree->PI_f_origin[battery] = maxOrigin;
		binaryTree->PI_f_batterySplit[battery] = maxBatterySplit;
	}
}

void LinearProgrammingSolver::tmpFunc(Tree<Tupple<int, double>> *binaryTree, int battery) {
	if (binaryTree != nullptr){
		for (auto edge : binaryTree->edges) {
			int newBattery;
			if(edge->getId() == -1)
				newBattery = battery;
			else
				newBattery = battery - 1;
			tmpFunc(edge->getChild(), newBattery);
		}
	}

	for(int i = 0; i <= battery; i++) {
		PI_r(binaryTree, i);
		PI_f(binaryTree, i);
	}
}

void LinearProgrammingSolver::findBestWalkId(Tree<Tupple<int, double>> *binaryTree, vector<int> *ids, int battery, bool returnToNode) {

	if(returnToNode)
	{
		if(binaryTree->getEdge(binaryTree->getPI_r_origin()[battery].getA()) != nullptr)//can be explorer
		{
			if (binaryTree->getEdge(binaryTree->getPI_r_origin()[battery].getB()) == nullptr)//no return to this node
			{
				int id = binaryTree->getPI_r_origin()[battery].getA();

				ids->push_back(id);

				findBestWalkId(binaryTree->getEdge(id)->getChild(), ids,
							   binaryTree->getPI_r_batterySplit()[battery].getA(), true);
			} else {
				Edge<Tupple<int, double>> *edge1 = binaryTree->getEdge(binaryTree->getPI_r_origin()[battery].getA());
				Edge<Tupple<int, double>> *edge2 = binaryTree->getEdge(binaryTree->getPI_r_origin()[battery].getB());

				ids->push_back(binaryTree->getPI_r_origin()[battery].getA());

				findBestWalkId(edge1->getChild(), ids, binaryTree->getPI_r_batterySplit()[battery].getA(), true);

				ids->push_back(binaryTree->getPI_r_origin()[battery].getB());

				findBestWalkId(edge2->getChild(), ids, binaryTree->getPI_r_batterySplit()[battery].getB(), true);
			}
		}
	}
	else
	{
		if(binaryTree->getEdge(binaryTree->getPI_f_origin()[battery].getA()) != nullptr)//can be explorer
		{
			if (binaryTree->getPI_f_origin()[battery].getB() == -1 && binaryTree->getPI_f_batterySplit()[battery].getB() == -1)//no return to this node
			{
				int id = binaryTree->getPI_f_origin()[battery].getA();

				ids->push_back(id);

				findBestWalkId(binaryTree->getEdge(id)->getChild(), ids,
							   binaryTree->getPI_f_batterySplit()[battery].getA(), false);
			} else {
				Edge<Tupple<int, double>> *edge1 = binaryTree->getEdge(binaryTree->getPI_f_origin()[battery].getA());
				Edge<Tupple<int, double>> *edge2 = binaryTree->getEdge(binaryTree->getPI_f_origin()[battery].getB());

				ids->push_back(binaryTree->getPI_f_origin()[battery].getA());

				findBestWalkId(edge1->getChild(), ids, binaryTree->getPI_f_batterySplit()[battery].getA(), true);

				ids->push_back(binaryTree->getPI_f_origin()[battery].getB());

				findBestWalkId(edge2->getChild(), ids, binaryTree->getPI_f_batterySplit()[battery].getB(), false);
			}
		}
	}


	if(binaryTree->getEdgeToParent() != nullptr && returnToNode)
		ids->push_back(binaryTree->getEdgeToParent()->getId());
}

void LinearProgrammingSolver::printSolution() {
	cout << "z=" << lp.getObjVal();

	for(int i = 1; i <= p; i++)
		cout << ";X" + to_string(i) + "=" << lp.getColPrim(i);

	for(int i = p + 1; i <= m + p; i++)
		cout << ";y" + to_string(i - p) + "=" << lp.getColPrim(i);

	cout << endl;
}

bool LinearProgrammingSolver::isInWalks(vector<vector<Edge<int> *>> walks,
                                        vector<Edge<int> *> walk) {
	bool flag = false;
	for(const auto &w: walks)
	{
		if(w.size() == walk.size())
		{
			flag = true;
			for(int i = 0; i < w.size(); i++)
				if(w[i] != walk[i]) {
					flag = false;
					break;
				}
			if(flag)
				return true;
		}
	}
	return false;
}

void LinearProgrammingSolver::printWalks(vector<vector<Edge<int> *>> vector) {
	int id = 1;
	for(auto v: vector) {
		cout << id <<" [" ;
		printWalk(v);
		cout << "]" << endl;
		id++;
	}
}

void
LinearProgrammingSolver::walkGenerator(vector<vector<Edge<int> *>> *outputVector,
                                       Edge<int> *origin,
                                       vector<Edge<int> *> currentWalk,
                                       int battery, Tree<int> *tree) {
	if(battery > 0)
	{
		if(origin != nullptr)
		{

			for(int i = 0; i < tree->edges.size(); i++)
			{
				if(tree->edges[i]->getId() != origin->getId()) {
					vector<Edge<int> *> newWalk = currentWalk;
					newWalk.push_back(tree->edges[i]);
					walkGenerator(outputVector, tree->edges[i], newWalk, battery - 1, tree->edges[i]->getChild());
				}
			}

			if(tree->edgeToParent != nullptr) {
				vector<Edge<int> *> newWalk = currentWalk;
				newWalk.push_back(tree->edgeToParent);
				walkGenerator(outputVector, tree->edgeToParent, newWalk, battery - 1, tree->edgeToParent->getParent());
			}
		}
		else{
			for(int i = 0; i < tree->edges.size(); i++)
			{
				vector<Edge<int> *> newWalk = currentWalk;
				newWalk.push_back(tree->edges[i]);
				walkGenerator(outputVector, tree->edges[i], newWalk, battery-1, tree->edges[i]->getChild());
			}
		}
	}
	else
		outputVector->push_back(currentWalk);
}

void LinearProgrammingSolver::printWalk(vector<Edge<int> *> vector) {
	for(auto e: vector)
		cout << "(" << e->getParent()->getLabel() << "<->" << e->getChild()->getLabel() << "), ";
}

AgentTreeExplorationSolution LinearProgrammingSolver::optiSolver(AgentTreeExplorationInstance *atei) {
	vector<vector<Edge<int> *>> walks;
	vector<Edge<int> *> tmp;

	walkGenerator(&walks, nullptr, tmp, atei->getStartingBattery(), atei->getTree());

	integerSolver(atei, walks);

	//printIntegerSolution();

	//printWalks(walks);

	return AgentTreeExplorationSolution(walks);
}

void LinearProgrammingSolver::initializeGlpkInteger(int p, int m, int agents) {
	lp = glpk_interface();

	this->p = p;
	this->m = m;

	lp.createProblem();
	lp.setProbName("atei");
	lp.setObjDir(glpk_interface::max);

	lp.addRows((m * 2) + 1);

	lp.setRowName(1, "alpha");
	lp.setRowBnds(1, glpk_interface::upper, 0.0, agents);

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
		lp.setColBnds(i, glpk_interface::lower, 0.0, 0.0);
		lp.setColKind(i, GLP_IV);
		lp.setObjCoef(i, 0.0);
	}

	for(int i = p + 1; i <= m + p; i++){
		string str = "y" + to_string(i - p);
		lp.setColName(i, str.c_str());
		lp.setColBnds(i, glpk_interface::lower, 0.0, 0.0);
		lp.setColKind(i, GLP_IV);
		lp.setObjCoef(i, 1.0);
	}

}

double fRand(double fMin, double fMax)
{
	srand(time(NULL));
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void LinearProgrammingSolver::printIntegerSolution() {
	cout << "z=" << lp.mipObjValue();

	for(int i = 1; i <= p; i++)
		cout << ";X" + to_string(i) + "=" << lp.mipColValue(i);

	for(int i = p + 1; i <= m + p; i++)
		cout << ";y" + to_string(i - p) + "=" << lp.mipColValue(i);

	cout << endl;
}

vector<vector<Edge<int> *>>
LinearProgrammingSolver::selectAleat(vector<vector<Edge<int> *>> walks, vector<double> proba, int k) {
	vector<vector<Edge<int> *>> result;
    double count = 0;
	for(int i = 0; i < proba.size(); i++)
    {
        count += proba[i];
    }

	double upperLimit = count;

	for(int i = 0; i < k; i++){
		double alpha = fRand(0, upperLimit);
		double cumul = 0;
		for(int j = 0; j < proba.size(); j++)
		{
			cumul += proba[j];
			if(cumul  > alpha)
			{
				result.push_back(walks[j]);
				upperLimit -= proba[j];
				walks[j] = walks.back();
				walks.pop_back();
				proba[j] = proba.back();
				proba.pop_back();
				break;
			}

		}
	}
	return result;
}

int LinearProgrammingSolver::doubellyCovered() {
	int counter = 0;
	for(auto val: weight)
	{
		if(val > 1)
			counter++;
	}
	return counter;
}

void LinearProgrammingSolver::integerSolver(AgentTreeExplorationInstance *atei, vector<vector<Edge<int>*>> walks) {
	int p = static_cast<int>(walks.size()), m = atei->getTree()->numberOfEdges();

	initializeGlpkInteger(p, m, atei->getNumberOfAgents());

	loadInstanceInGlpk(atei, walks);

	lp.simplex(nullptr);
	lp.int_opt(nullptr);
}