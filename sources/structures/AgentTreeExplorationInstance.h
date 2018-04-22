//
// Created by raphael on 4/19/18.
//

#ifndef TREE_EXPLORER_AGENTTREEEXPLORATIONINSTANCE_H
#define TREE_EXPLORER_AGENTTREEEXPLORATIONINSTANCE_H

#include <ostream>
#include "SimpleTree.h"
/**
 * \class AgentTreeExplorationInstance
 *
 * \ingroup //TODO: find out
 *
 * \brief k agent exploration instance
 *
 * Instance of the k agent tree exploration problem.
 *
 * \author Raphael Sturgis $Author: bv $
 *
 * \version $Revision: 0.1 $
 *
 * \date $Date: 2018/04/19 16:42:01 $
 *
 * Contact: raphael.sturgis@etu.univ-amu.fr
 *
 */

class AgentTreeExplorationInstance {
private:
	SimpleTree tree;        ///Tree to explore
	int numberOfAgents;     ///Number of agents
	int startingBattery;    ///Battery at root for all agents
public:
	/**
	 * Constructor
	 * @param tree
	 * @param numberOfAgents
	 * @param startingBattery
	 */
	AgentTreeExplorationInstance(const SimpleTree &tree, int numberOfAgents,
	                             int startingBattery) : tree(
			tree), numberOfAgents(numberOfAgents), startingBattery(
			startingBattery) {};

	/**
	 * Simple getter
	 * @return Tree
	 */
	const SimpleTree &getTree() const {
		return tree;
	}

	/**
	 * Simple getter
	 * @return number of agents
	 */
	int getNumberOfAgents() const {
		return numberOfAgents;
	}

	/**
	 * Simple getter
	 * @return starting battery
	 */
	int getStartingBattery() const {
		return startingBattery;
	}

	/**
	 * Equality operator
	 * @param rhs
	 * @return true/false
	 */
	bool operator==(const AgentTreeExplorationInstance &rhs) const {
		return tree == rhs.tree &&
		       numberOfAgents == rhs.numberOfAgents &&
		       startingBattery == rhs.startingBattery;
	}

	bool operator!=(const AgentTreeExplorationInstance &rhs) const {
		return !(rhs == *this);
	}

	friend ostream &
	operator<<(ostream &os, const AgentTreeExplorationInstance &instance) {
		os << instance.numberOfAgents << " " << instance.startingBattery << "\n"
		   << instance.tree << "\n";
		return os;
	}
};
#endif //TREE_EXPLORER_AGENTTREEEXPLORATIONINSTANCE_H
