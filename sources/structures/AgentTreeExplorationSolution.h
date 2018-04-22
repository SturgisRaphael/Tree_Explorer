//
// Created by raphael on 4/20/18.
//

#ifndef TREE_EXPLORER_AGENTREEEXPLORATIONSOLUTION_H
#define TREE_EXPLORER_AGENTREEEXPLORATIONSOLUTION_H

/**
 * Gives function and structures for outputting a solution to the tree
 * exploration problem
 */

#include <vector>
#include <ostream>
#include "AgentTreeExplorationInstance.h"

using namespace std;

class AgentTreeExplorationSolution {
private:
	vector<vector<int>> walks;  ///walks used in solution
	int numberOfEdgesExplored;  ///number of edges explored
public:
	/**
	 * Constructor
	 */
	AgentTreeExplorationSolution() {}

	/**
	 * checks if solution is a valid solution to the problem
	 * @note does not check optimality
	 * @param instance
	 * @return is Valid (True|False)
	 */
	bool isValid(AgentTreeExplorationInstance instance) {
		int battery = instance.getStartingBattery();
		for(auto w: walks)
			if(w.size() > battery)
				return false;

		//TODO: check validity of numberOfEdges
		return true;
	}

	/**
	 * Simple getter
	 * @return walks
	 */
	const vector<vector<int>> &getWalks() const {
		return walks;
	}

	/**
	 * Simple setter
	 * @param walks
	 */
	void setWalks(const vector<vector<int>> &walks) {
		AgentTreeExplorationSolution::walks = walks;
	}

	/**
	 * Simple getter
	 * @return numberOfEdgesExplored
	 */
	int getNumberOfEdgesExplored() const {
		return numberOfEdgesExplored;
	}

	/**
	 * Simple setter
	 * @param numberOfEdgesExplored
	 */
	void setNumberOfEdgesExplored(int numberOfEdgesExplored) {
		AgentTreeExplorationSolution::numberOfEdgesExplored = numberOfEdgesExplored;
	}

	friend ostream &
	operator<<(ostream &os, const AgentTreeExplorationSolution &solution) {
		os //<< "walks: " << solution.walks << "\n" //TODO: print walks
		   << " numberOfEdgesExplored: " << solution.numberOfEdgesExplored <<"\n";
		return os;
	}
};


#endif //TREE_EXPLORER_AGENTREEEXPLORATIONSOLUTION_H
