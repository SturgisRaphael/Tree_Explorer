/**
 * \class Tree
 *
 * \ingroup utils
 *
 * \brief Tree
 *
 * This a non-oriented, weighted Tree. Weight type is defined at construction
 * . Gives usefull function to build and explore a tree.
 *
 * \author Raphael Sturgis $Author: bv $
 *
 * \version $Revision: 0.1 $
 *
 * \date $Date: 2018/04/18 17:48:01 $
 *
 * Contact: raphael.sturgis@etu.univ-amu.fr
 *
 */

#ifndef TREE_EXPLORER_TREE_H
#define TREE_EXPLORER_TREE_H

#include <string>
#include <vector>
#include <ostream>

using namespace std;

template <class T>
class Tree {
protected:
	string label = "no label";
	T weightFromParent = NULL;
	Tree* parent = nullptr;
	vector<Tree*> childs;

public:
	///Create a tree
	Tree(){Tree("unnamed", nullptr);};

	///Create a tree using a label
	Tree(const string &label):label(label) {};


	///Create a tree using a label and parent
	Tree(const string &label, Tree *parent):label(label), parent(parent) {};

	///Create a tree using a label, a parent and a weight
	Tree(const string &label, T weightFromParent, Tree *parent) : label(label),
	                                                              weightFromParent(
			                                                              weightFromParent),
	                                                              parent(parent) {}

	/**
	 * Simple getter
	 * @return label
	 */
	const string &getLabel() const{return label;};

	virtual /**
	 * Simple getter
	 * @return parent
	 */
	Tree *getParent() const{return parent;};

	/**
	 * Simple getter
	 * @return childs
	 */
	const vector<Tree<T> *> &getChilds() const{return childs;};

	/**
	 * Simple getter
	 * @return weight from parent
	 */
	T getWeightFromParent() const{
		return weightFromParent;
	};

	virtual /**
	 * Adds a child to the tree
	 * @param child subTree
	 * @param weight of the edge between the current node and its child node
	 */
	bool addChild(Tree<T> *child, T weight){
		for(auto c : this->childs)
			if(c == child || c->label == child->label)
				return false;
		child->parent = this;
		child->weightFromParent = weight;
		this->childs.push_back(child);
		return true;
	};

	virtual /**
	 * Adds a child to the tree
	 * @param label
	 * @param weight
	 * @return
	 */
	bool addChild(string label, T weight){
		for(auto c : this->childs)
			if(c->label == label)
				return false;
		Tree *child = new Tree(label, weight, this);
		this->childs.push_back(child);
		return true;
	}

	/**
	 * Simple getter
	 * @return number of childs
	 */
	long getNumberOfChilds(){return childs.size();};

	virtual /**
	 * Simple getter
	 * @param index of child to return
	 * @return child
	 */
	Tree* getChild(int index){
		if(childs.size() >= index)
			return nullptr;
		return childs[index];
	};

	virtual /**
	 * Simple getter
	 * @param label of child to return
	 * @return child
	 */
	Tree* getChild(string label){
		for(Tree* child : childs)
			if(child->label == label)
				return child;
		return nullptr;
	};

	friend ostream &operator<<(ostream &os, const Tree &tree) {
		Tree* tmp = tree.getParent();

		if(tmp == nullptr)
			os << tree.label << "\n";
		else {
			while (tmp != nullptr) {
				os << "-";
				tmp = tmp->getParent();
			}

			os << " " << tree.label << ", " << tree.weightFromParent << "\n";
		}
		for (auto c : tree.childs)
			os << *c;
		return os;
	};

	bool operator==(const Tree &rhs) const {
		if(childs.size() != rhs.childs.size())
			return false;
		for(int i = 0; i < childs.size(); i++)
		{
			if(*childs[i] != *rhs.childs[i])
				return false;
		}
		return label == rhs.label &&
		       weightFromParent == rhs.weightFromParent;
	}

	bool operator!=(const Tree &rhs) const {
		return !(rhs == *this);
	}
};

#endif //TREE_EXPLORER_TREE_H
