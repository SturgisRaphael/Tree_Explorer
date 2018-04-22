//
// Created by raphael on 4/20/18.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "FileManager.h"

AgentTreeExplorationInstance FileManager::readInstanceFromFile(string path) {
	int k = -1, b = -1;
	std::ifstream infile(path);
	std::string line;

	std::getline(infile, line);

	std::istringstream iss(line);

	iss >> k >> b;
	if(k == -1 || b == -1)
	{
		cerr << "ERROR: bad file" << endl;
		exit(1);
	}


	std::getline(infile, line);
	auto *root = new SimpleTree(line);
	SimpleTree *current_parent = root, *tmp = root;

	int current_level = 0, i;
    while (std::getline(infile, line)) {
    	if(line.empty())
    		break;
	    for (i = 0; line[i] == '-'; i++);
	    if(current_level + 1 < i || i == 0){
	    	cerr << "ERROR: bad file" << endl;
	    	exit(1);
	    }
	    else if (i == current_level)//add a child
	    {
		    current_parent->addChild(line.substr(
				    static_cast<unsigned long>(i + 1)));
		    tmp = current_parent->getChild(line.substr(
				    static_cast<unsigned long>(i + 1)));
	    } else if (i == current_level + 1)//add a grand son
	    {
		    current_level++;
		    current_parent = tmp;
		    current_parent->addChild(line.substr(
				    static_cast<unsigned long>(i + 1)));
		    tmp = current_parent->getChild(line.substr(
				    static_cast<unsigned long>(i + 1)));
	    }
	    else{
	    	for(current_level; current_level > i; current_level--)
	    		current_parent = current_parent->getParent();
		    current_parent->addChild(line.substr(
				    static_cast<unsigned long>(i + 1)));
		    tmp = current_parent->getChild(line.substr(
				    static_cast<unsigned long>(i + 1)));
	    }
    }

	return AgentTreeExplorationInstance(*root, k, b);
}

void FileManager::writeInstanceToFile(string path,
                                      AgentTreeExplorationInstance instance) {
	ofstream myfile (path);
	if (myfile.is_open())
	{
		myfile << instance;
		myfile.close();
	}
	else cout << "Unable to open file";
}

void FileManager::writeSolutionToFile(string path,
                                      AgentTreeExplorationSolution solution) {

}
