//
// Created by raphael on 4/19/18.
//

#ifndef TREE_EXPLORER_TUPPLE_H
#define TREE_EXPLORER_TUPPLE_H

#include <ostream>

using namespace std;

template <class A, class B>
class Tupple {
private:
	A a = static_cast<A>(-1);
	B b = static_cast<B>(-1);
public:
	Tupple() {}

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

	bool operator==(const Tupple &rhs) const {
		return a == rhs.a &&
			   b == rhs.b;
	}

	bool operator!=(const Tupple &rhs) const {
		return !(rhs == *this);
	}

	friend ostream &operator<<(ostream &os, const Tupple &tupple) {
		os << "(" << tupple.a << "," << tupple.b << ")";
		return os;
	}
};

#endif //TREE_EXPLORER_TUPPLE_H