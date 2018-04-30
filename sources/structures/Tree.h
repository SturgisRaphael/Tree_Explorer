//
// Created by zampieri on 26/04/18.
//

#ifndef TREE_EXPLORER_TREE_H
#define TREE_EXPLORER_TREE_H

#include <string>
#include <vector>
#include <ostream>
#include "Edge.h"
#include "Tupple.h"

#define MAX_BATTERY 10000

using namespace std;

template <class T>
class Tree {
protected:
	string label = "no label";		    ///label for current node
	Edge<T>* edgeToParent = nullptr;	///pointer to parent if he exists
	vector<Edge<T>*> edges;			    ///list of child nodes
	double PI_r[MAX_BATTERY];
	double PI_f[MAX_BATTERY];

	Tupple<int, int> PI_r_origin[MAX_BATTERY];
	Tupple<int, int> PI_f_origin[MAX_BATTERY];

	Tupple<int, int> PI_r_batterySplit[MAX_BATTERY];
	Tupple<int, int> PI_f_batterySplit[MAX_BATTERY];

	friend class LinearProgrammingSolver;

public:
	explicit Tree(const string &label) : label(label) {Edge<T>::reset();}

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

	/**
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
		return nullptr;
	}

	Tree* addChild(string label){
		for(Edge<T>*c : this->edges)
			if(c->getChild()->label == label)
				return nullptr;
		auto *child = new Tree(label, nullptr);
		auto *edge = new Edge<T>(this, child);
		child->setEdgeToParent(edge);
		this->edges.push_back(edge);
		return child;
	}

	Tree* addChild(string label, long id){
		return addChild(label, id, 0);
	}

	Tree* addChild(string label, long id, T weight){
		for(Edge<T>*c : this->edges)
			if(c->getChild()->label == label)
				return nullptr;
		auto *child = new Tree<T>(label, nullptr);
		auto *edge = new Edge<T>(this, child, id, weight);
		child->setEdgeToParent(edge);
		this->edges.push_back(edge);
		return child;
	}

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

				auto *relay = new Tree("Null");
				tmp->setParent(relay);
				relay->addEdge(tmp);

				auto *nullEdge = new Edge<T>(this, relay, -1, nullWeight);

				Tree<T>::edges[1] = nullEdge;
				relay->setEdgeToParent(nullEdge);

				auto *child = new Tree<T>(label, nullptr);
				auto *edge = new Edge<T>(relay, child, id, weight);
				child->setEdgeToParent(edge);
				relay->edges.push_back(edge);
				return child;
			}
			else
			{
				return tmp->getChild()->addChildBin(label, id, weight, nullWeight);
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
				T weight = tree->edges[i]->getWeight();
				tree->addChildBin(label, id, weight, nullWeight);
				this->binarize(tree->getChild(i), nullWeight);
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

	void addEdge(Edge<T> *pEdge) {
		edges.push_back(pEdge);
	}
};


#endif //TREE_EXPLORER_TREE_H
