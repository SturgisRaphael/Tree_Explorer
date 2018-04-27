//
// Created by raphael on 4/20/18.
//

#ifndef TREE_EXPLORER_FILEMANAGER_H
#define TREE_EXPLORER_FILEMANAGER_H
/**
 * Class task to give function reading and writing solution to and from files
 */

#include "../structures/AgentTreeExplorationInstance.h"
#include "../structures/AgentTreeExplorationSolution.h"

class FileManager {
public:
	/**
	 * Reads a file containning an instance of our problem
	 * @param path of the file
	 * @return The instance
	 */
	static AgentTreeExplorationInstance readInstanceFromFile(string path);

	/**
	 * Writes instances of the problem to file system
	 * @param path
	 * @param instance
	 */
	static void writeInstanceToFile(string path, AgentTreeExplorationInstance
	*instance);

	/**
	 * Writes solution to the problem to file
	 * @param path
	 * @param solution
	 */
	void writeSolutionToFile(string path, AgentTreeExplorationSolution
	solution);
};


#endif //TREE_EXPLORER_FILEMANAGER_H
