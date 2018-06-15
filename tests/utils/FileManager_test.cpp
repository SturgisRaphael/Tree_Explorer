//
// Created by raphael on 4/20/18.
//

#include <gtest/gtest.h>
#include "../../sources/structures/AgentTreeExplorationInstance.h"
#include "../../sources/utils/FileManager.h"

TEST(Read, test1) {
	AgentTreeExplorationInstance *atei =
			FileManager::readInstanceFromFile("../data/testFiles/test1.1.txt");

	int index = 0;

	Tree<int>* tree = new Tree<int>(&index, "root");
	tree->addChild("1");
	tree->addChild("2");
	tree->addChild("3");
	tree->getChild("3")->addChild("3.1");
	tree->getChild("3")->addChild("3.2");

	AgentTreeExplorationInstance comp =
			AgentTreeExplorationInstance(tree, 4, 4);
	ASSERT_EQ(comp, *atei);
}

TEST(Read, test2){
	AgentTreeExplorationInstance *atei =
			FileManager::readInstanceFromFile("../data/testFiles/test1.2.txt");


	int index = 0;

	Tree<int>* tree = new Tree<int>(&index, "root");
	tree->addChild("1");
	tree->addChild("2");
	tree->getChild("2")->addChild("2.1");
	tree->getChild("2")->getChild("2.1")->addChild("2.1.1");
	tree->getChild("2")->getChild("2.1")->addChild("2.1.2");
	tree->getChild("2")->addChild("2.2");
	tree->getChild("2")->getChild("2.2")->addChild("2.2.1");
	tree->addChild("3");
	tree->addChild("4");
	tree->getChild("4")->addChild("4.1");
	AgentTreeExplorationInstance comp =
			AgentTreeExplorationInstance(tree, 3, 5);
	ASSERT_EQ(comp ,*atei);
}


TEST(Read, test3) {
	AgentTreeExplorationInstance *atei =
			FileManager::readInstanceFromFile("../data/testFiles/test1.3.txt");

	int index = 0;

	Tree<int>* tree = new Tree<int>(&index, "root");
	AgentTreeExplorationInstance comp =
			AgentTreeExplorationInstance(tree, 1, 1);
	ASSERT_TRUE(comp == *atei);
}

TEST(Read, bad_file_1) {
	ASSERT_EXIT
	(FileManager::readInstanceFromFile("../data/testFiles/test1.fail.txt"),
	 ::testing::ExitedWithCode(1), "ERROR: bad file");
}

TEST(Read, bad_file_2) {
	ASSERT_EXIT
	(FileManager::readInstanceFromFile("../data/testFiles/test2.fail.txt"),
	 ::testing::ExitedWithCode(1), "ERROR: bad file");
}

TEST(Write, instance1) {
	int index = 0;

	Tree<int>* tree = new Tree<int>(&index, "root");
	tree->addChild("1");
	tree->addChild("2");
	tree->addChild("3");
	tree->getChild("3")->addChild("3.1");
	tree->getChild("3")->addChild("3.2");
	AgentTreeExplorationInstance comp =
			AgentTreeExplorationInstance(tree, 3, 2);

	FileManager::writeInstanceToFile("../data/testFiles/test2.1.txt", &comp);

	AgentTreeExplorationInstance *atei = FileManager::readInstanceFromFile("../data/testFiles/test2.1.txt");

	ASSERT_EQ(comp, *atei);

}