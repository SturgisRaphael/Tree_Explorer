//
// Created by raphael on 4/20/18.
//

#ifndef TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H
#define TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H

#include <glpk.h>
#include "../structures/AgentTreeExplorationSolution.h"
#include "../structures/TuppleTree.h"

class LinearProgrammingSolver {
public:
	AgentTreeExplorationSolution solver(AgentTreeExplorationInstance);

	TuppleTree betaTreegenerator(AgentTreeExplorationInstance);


};


#endif //TREE_EXPLORER_LINEARPROGRAMMINGSOLVER_H
