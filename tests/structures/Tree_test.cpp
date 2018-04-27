//
// Created by raphael on 4/22/18.
//

#include <gtest/gtest.h>
#include "../../sources/structures/Tree.h"


TEST(Tree, countEdges) {
	Tree<int> tree = Tree<int>("root");
	tree.addChild("1");
	tree.addChild("2");
	tree.addChild("3");
	tree.getChild("3")->addChild("3.1");
	tree.getChild("3")->addChild("3.2");

	ASSERT_EQ(tree.numberOfEdges(), 5);
}


TEST(Tree, Tree_Equality_Test) {
	Tree<int> tree1 = Tree<int>("root");
	tree1.addChild("1");
	tree1.addChild("2");
	tree1.addChild("3");
	tree1.getChild("3")->addChild("3.1");
	tree1.getChild("3")->addChild("3.2");

	Tree<int> tree2 = Tree<int>("root");
	tree2.addChild("1");
	tree2.addChild("2");
	tree2.addChild("3");
	tree2.getChild("3")->addChild("3.1");
	tree2.getChild("3")->addChild("3.2");

	Tree<int> tree3 = Tree<int>("root");
	tree3.addChild("1");
	tree3.addChild("2");
	tree3.getChild("2")->addChild("2.1");
	tree3.addChild("3");
	tree3.getChild("3")->addChild("3.1");
	tree3.getChild("3")->addChild("3.2");

	Tree<int> tree4 = Tree<int>("root");
	tree4.addChild("1");
	tree4.addChild("3");

	ASSERT_TRUE(tree1 == tree2);
	ASSERT_FALSE(tree1 == tree3);
	ASSERT_FALSE(tree1 == tree4);
}

TEST(BinaryTree, all) {
	Tree<int> binaryTree = Tree<int>("root");
	binaryTree.addChildBin("1", 1, 0, 0);
	binaryTree.addChildBin("2", 2, 0, 0);
	binaryTree.addChildBin("3", 3, 0, 0);
	binaryTree.addChildBin("4", 4, 0, 0);

	binaryTree.binarize(-1);

	Tree<int> comp = Tree<int>("root");
	comp.addChild("1");
	comp.addChild("Null");
	comp.getChild("Null")->addChild("2");
	comp.getChild("Null")->addChild("Null");
	comp.getChild("Null")->getChild("Null")->addChild("3");
	comp.getChild("Null")->getChild("Null")->addChild("4");

	ASSERT_EQ(binaryTree, comp);
}