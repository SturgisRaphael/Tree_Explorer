//
// Created by raphael on 4/19/18.
//

#ifndef TREE_EXPLORER_TUPPLE_H
#define TREE_EXPLORER_TUPPLE_H

template <class A, class B>
class Tupple {
private:
	A a;
	B b;
public:
	Tupple(A a, B b) : a(a), b(b) {};

	/**
	 * Simple getter
	 * @return first element in tupple
	 */
	A getA() const {
		return a;
	}

	/**
	 * simple getter
	 * @return second element in tupple
	 */
	B getB() const {
		return b;
	}
};

#endif //TREE_EXPLORER_TUPPLE_H