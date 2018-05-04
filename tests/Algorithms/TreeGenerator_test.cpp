//
// Created by zampieri on 04/05/18.
//

#include <gtest/gtest.h>
#include "../../sources/structures/Tree.h"
#include "../../sources/algortihms/TreeGenerator.h"

TEST(generateBinaryTrees, test1) {
	vector<Tree<int>*> vector = TreeGenerator::generateBinaryTrees(1);

	ASSERT_EQ(vector.size(), 3);
}

TEST(generateBinaryTrees, test2) {
	vector<Tree<int>*> vector = TreeGenerator::generateBinaryTrees(2);

	ASSERT_EQ(vector.size(), 13);
}
