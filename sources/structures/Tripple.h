//
// Created by zampieri on 26/04/18.
//

#ifndef TREE_EXPLORER_TRIPPLE_H
#define TREE_EXPLORER_TRIPPLE_H

#include <ostream>

template <class A, class B, class C>
class Tripple {
	A a;
	B b;
	C c;

public:
	Tripple(A a, B b, C c) : a(a), b(b), c(c) {}

	A getA() const {
		return a;
	}

	B getB() const {
		return b;
	}

	C getC() const {
		return c;
	}

	bool operator==(const Tripple &rhs) const {
		return a == rhs.a &&
			   b == rhs.b &&
			   c == rhs.c;
	}

	bool operator!=(const Tripple &rhs) const {
		return !(rhs == *this);
	}

	friend std::ostream &operator<<(std::ostream &os, const Tripple &tripple) {
		os << "(" << tripple.a << "," << tripple.b << "," << tripple.c << ")";
		return os;
	}
};


#endif //TREE_EXPLORER_TRIPPLE_H
