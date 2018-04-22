//
// Created by raphael on 4/19/18.
//


#include <iostream>
#include "utils/Tree.h"

int main(int argc, char* argv[])
{
	Tree<int> t, *c = new Tree<int>("child", nullptr);
	t.addChild(c, 10);
	cout << t;
}