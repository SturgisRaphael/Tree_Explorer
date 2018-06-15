//
// Created by raphael on 5/29/18.
//

#include "gloutonSolver.h"

AgentTreeExplorationSolution gloutonSolver::solver(AgentTreeExplorationInstance *atei) {
    auto *matrix = static_cast<double *>(malloc(atei->getTree()->numberOfEdges() * sizeof(double)));
    vector<vector<Edge<int> *>> solution;
    for(int i = 0; i < atei->getTree()->numberOfEdges(); i++)
        matrix[i] = 1;
    for(int i = 0; i < atei->getNumberOfAgents(); i++){
        LinearProgrammingSolver util;

        Tree<Tupple<int, double>> *binaryTree = util.makeBinaryTree(atei->getTree(), matrix);

        double bestSumBeta_i = 0;
        vector<Edge<int> *> newWalk = util.findBestWalk(atei->getTree(), binaryTree, atei->getStartingBattery(), &bestSumBeta_i);
        solution.push_back(newWalk);
        for(Edge<int>* j: newWalk)
        {
            matrix[j->getId()] = 0;
        }
        delete binaryTree;
    }
    free(matrix);
    return AgentTreeExplorationSolution(solution);
}
