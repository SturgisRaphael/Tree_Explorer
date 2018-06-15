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
	vector<vector<Edge<int> *>> walks;  ///walks used in solution
	int numberOfEdgesExplored;  ///number of edges explored
	int numberOfEdgesDoublellyExplored;
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
	const vector<vector<Edge<int> *>> &getWalks() const {
		return walks;
	}

	/**
	 * Simple setter
	 * @param walks
	 */
	void setWalks(const vector<vector<Edge<int> *>> &walks) {
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

	AgentTreeExplorationSolution(vector<vector<Edge<int> *>> vect) {
		this->walks = vect;
		numberOfEdgesExplored = 0;
		numberOfEdgesDoublellyExplored = 0;
		vector<int> ids;
		vector<int> doubleExplored;
		for(vector<Edge<int> *> edges : vect)
		{
			for(Edge<int> * edge : edges)
			{
				bool hasBeenSeen = false;
				for(int id: ids)
				{
					if(id == edge->getId())
					{
						hasBeenSeen = true;
                        bool hasBeenSeen2 = false;
						for(int d: doubleExplored)
                        {
                            if(d == edge->getId())
                            {
                                hasBeenSeen2 = true;
                                break;
                            }
                        }
                        if(!hasBeenSeen2)
                        {
                            doubleExplored.push_back(edge->getId());
                            numberOfEdgesDoublellyExplored++;
                        }
					}
				}
				if(!hasBeenSeen)
				{
					ids.push_back(edge->getId());
					numberOfEdgesExplored++;
				}
			}
		}
	}

    int getNumberOfEdgesDoublellyExplored() const {
        return numberOfEdgesDoublellyExplored;
    }

    void setNumberOfEdgesDoublellyExplored(int numberOfEdgesDoublellyExplored) {
        AgentTreeExplorationSolution::numberOfEdgesDoublellyExplored = numberOfEdgesDoublellyExplored;
    }
};


#endif //TREE_EXPLORER_AGENTREEEXPLORATIONSOLUTION_H
