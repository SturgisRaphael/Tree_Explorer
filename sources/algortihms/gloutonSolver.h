//
// Created by raphael on 5/29/18.
//

#ifndef TREE_EXPLORER_GLOUTONSOLVER_H
#define TREE_EXPLORER_GLOUTONSOLVER_H


#include "../structures/AgentTreeExplorationSolution.h"
#include "LinearProgrammingSolver.h"

class gloutonSolver {
public:
    static AgentTreeExplorationSolution solver(AgentTreeExplorationInstance *atei);
};


#endif //TREE_EXPLORER_GLOUTONSOLVER_H
