//
// Created by raphael on 4/19/18.
//

#ifndef TREE_EXPLORER_SIMPLETREE_H
#define TREE_EXPLORER_SIMPLETREE_H


#include <ostream>
#include "Tree.h"

class SimpleTree : public Tree<int> {
public:
	///Constructor
	SimpleTree(){}

	///Constructor
	SimpleTree(const string &label) : Tree(label) {}

	SimpleTree(const string &label, SimpleTree *parent) : Tree(label, parent) {}

	/**
	 * ban use of function
	 * @return false
	 */
	bool addChild(Tree<int> *child, int weight) override{return false;};

	/**
	 * ban use of function
	 * @return false
	 */
	bool addChild(string label, int weight) override {return false;}

	/**
	 *
	 * @param child to add to the Tree
	 * @return did it work?
	 */
	bool addChild(SimpleTree *child){
		return Tree::addChild(child, 1);
	};

	/**
	 *
	 * @param child to add to the Tree
	 * @return did it work?
	 */
	bool addChild(string label){
		for(auto c : this->childs)
			if(c->getLabel() == label)
				return false;
		SimpleTree *child = new SimpleTree(label, this);
		this->childs.push_back(child);
		return true;
	}

	SimpleTree *getChild(int index) override {
		return dynamic_cast<SimpleTree *>(Tree::getChild(index));
	}

	SimpleTree *getChild(string label) override {
		return dynamic_cast<SimpleTree *>(Tree::getChild(label));
	}

	SimpleTree *getParent() const override {
		return dynamic_cast<SimpleTree *>(Tree::getParent());
	}

	friend ostream &operator<<(ostream &os, const SimpleTree &tree) {
		Tree* tmp = tree.getParent();

		if(tmp == nullptr)
			os << tree.label << "\n";
		else {
			while (tmp != nullptr) {
				os << "-";
				tmp = tmp->getParent();
			}

			os << " " << tree.label << "\n";
		}
		for (auto c : tree.childs)
			os << *dynamic_cast<SimpleTree *>(c);
		return os;
	}
};


#endif //TREE_EXPLORER_SIMPLETREE_H
