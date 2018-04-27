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
#include "Edge.h"
#include "BinaryTree.h"

using namespace std;

template <class T>
class Tree {
protected:
	string label = "no label";		///label for current node
	Edge<T>* edgeToParent = nullptr;	///pointer to parent if he exists
	vector<Edge<T>*> edges;			///list of child nodes
	friend class LinearProgrammingSolver;

public:
	Tree() {}

	Tree(const string &label) : label(label) {Edge<int>::reset();}

	Tree(const string &label, Edge<T> *edgeToParent) : label(label), edgeToParent(edgeToParent) {}

	const string &getLabel() const {
		return label;
	}

	Edge<T> *getEdgeToParent() const {
		return edgeToParent;
	}

	void setEdgeToParent(Edge<T> *edgeToParent) {
		Tree::edgeToParent = edgeToParent;
	}

	bool operator==(const Tree &rhs) const {
		if(rhs.edges.size() != edges.size())
			return false;
		for(int i = 0; i < edges.size(); i++)
			if(*getChild(i)!= *rhs.getChild(i))
				return false;
		return label == rhs.label;
	}

	bool operator!=(const Tree &rhs) const {
		return !(rhs == *this);
	}

	friend ostream &operator<<(ostream &os, const Tree &tree) {
		Edge<T>* tmp = tree.getEdgeToParent();

		if(tmp == nullptr)
			os << tree.label << "\n";

		else
		{
			while (tmp != nullptr) {
				os << "-";
				tmp = tmp->getParent()->getEdgeToParent();
			}

			os << " " << tree.label << "\n";
		}

		for (auto c : tree.edges)
			os << *c->getChild();


		return os;
	}

	/**
	 * Simple getter
	 * @param index
	 * @return child
	 */
	Tree * getChild(int index)const {
		if(edges.size() <= index)
			return nullptr;
		return edges[index]->getChild();
	}

	virtual /**
	 * Simple getter
	 * @param label
	 * @return child
	 */
	Tree* getChild(string label){
		for(Edge<T>* edge : edges)
			if(edge->getChild()->label == label)
				return edge->getChild();
		return nullptr;
	}

	Edge<T>* getEdge(string label)
	{
		for(Edge<T>* edge : edges)
			if(edge->getChild()->label == label)
				return edge;
		return NULL;
	}

	/**
	 * adds a child to current node
	 * @param child
	 * @return succes
	 */
	Tree* addChild(Tree *child){
		for(Edge<T> c : this->edges)
			if(c.getChild() == child || c.getChild()->label == child->label)
				return nullptr;
		Edge<T> *edge = new Edge<T>(this, child);
		child->edgeToParent = edge;
		this->edges.push_back(edge);
		return child;
	}

	Tree* addChild(string label){
		for(Edge<T>*c : this->edges)
			if(c->getChild()->label == label)
				return nullptr;
		Tree *child = new Tree(label, nullptr);
		Edge<T> *edge = new Edge<T>(this, child);
		child->setEdgeToParent(edge);
		this->edges.push_back(edge);
		return child;
	}

	Tree* addChild(string label, long id){
		for(Edge<T>*c : this->edges)
			if(c->getChild()->label == label)
				return nullptr;
		Tree *child = new Tree(label, nullptr);
		Edge<T> *edge = new Edge<T>(this, child);
		child->setEdgeToParent(edge);
		this->edges.push_back(edge);
		return child;
	}

	Tree* addChild(string label, long id, T weight){
		for(Edge<T>*c : this->edges)
			if(c->getChild()->label == label)
				return nullptr;
		Tree<T> *child = new Tree<T>(label, nullptr);
		Edge<T> *edge = new Edge<T>(this, child, weight);
		child->setEdgeToParent(edge);
		this->edges.push_back(edge);
		return child;
	}

	void addEdge(Edge<T> *pEdge);

	Tree<T> *addChildBin(string label, long id, T weight, T nullWeight) {
		for (Edge<T> *c : this->edges)
			if (c->getChild()->getLabel() == label)
				return nullptr;
		if (Tree<T>::edges.size() < 2)
		{
			return addChild(label, id, weight);
		}
		else{
			Edge<T> *tmp = Tree<T>::edges[1];

			if (tmp->getChild()->getLabel() != "Null") {

				Tree<T> *relay = new Tree("Null");
				tmp->setParent(relay);
				relay->addEdge(tmp);

				Edge<T> *nullEdge = new Edge<T>(this, relay, -1, nullWeight);

				Tree<T>::edges[1] = nullEdge;
				relay->setEdgeToParent(nullEdge);

				Tree<T> *child = new Tree<T>(label, nullptr);
				Edge<T> *edge = new Edge<T>(relay, child, id, weight);
				child->setEdgeToParent(edge);
				relay->edges.push_back(edge);
				return child;
			}
			else
			{
				return tmp->getChild()->addChild(label);
			}
		}
	}

	void binarize(T nullWeight){
		auto *tree = new Tree<T>(this->getLabel());
		binarize(tree, nullWeight);
	}

	void binarize(Tree<T> *tree, T nullWeight)
	{
		if(tree->edges.size() != 0)
		{
			for(int i = 0; i < tree->edges.size(); i++)
			{
				int id = tree->edges[i]->getId();
				string label = tree->edges[i]->getChild()->getLabel();
				T weight = tree->edges[i]->getChild()->getWeight();
				tree->addChildBin(label, id, weight, nullWeight);
				this->binarize(tree->getChild(i));
			}
		}
	}

	/**
	 * Counts number of edges in Tree
	 * @return
	 */
	int numberOfEdges()const {
		if(edges.empty())
			return 0;
		else
		{
			int sum = 0;
			for(Edge<T>* ed: edges)
				sum += ed->getChild()->numberOfEdges() + 1;
			return sum;
		}
	}

	/**
	 * counts the number of nodes
	 * @return number of nodes
	 */
	int numberOfNodes()const {
		if(edges.empty())
			return 1;
		else
		{
			int sum = 0;
			for(Edge<T>* ed: edges)
				sum += ed->getChild()->numberOfEdges();
			return sum;
		}
	}

	virtual ~Tree() {
		for(Edge<T>* ed: edges)
			delete ed;
	}

	Tree<T> *copy()
	{
		auto *tree = new Tree<T>(this->getLabel());
		copy(tree);
		return tree;
	}

private:
	void copy(Tree<T> *tree){
		if(tree->edges.size() != 0)
		{
			for(int i = 0; i < tree->edges.size(); i++)
			{
				int id = tree->edges[i]->getId();
				string label = tree->edges[i]->getChild()->getLabel();
				T weight = tree->edges[i]->getChild()->getWeight();
				tree->addChild(label, id, weight);
				this->copy(tree->getChild(i));
			}
		}
	}
};

template<class T>
void Tree<T>::addEdge(Edge<T> *pEdge) {
	edges.push_back(pEdge);
}

#endif //TREE_EXPLORER_TREE_H
