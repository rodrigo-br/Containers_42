#ifndef NODE_H
#define NODE_H

#include "utility.hpp"

namespace ft {

	template<class Pair> struct Node {
		typedef Pair		value_type;
		typedef Node*		pointer;
		typedef Node&		reference;
		typedef const Node&	const_reference;
		pointer				parent;
		pointer				left;
		pointer				right;
		value_type			value;

		Node() : parent(NULL), left(NULL), right(NULL), value() {};

		Node(const value_type &data) : parent(NULL), left(NULL), right(NULL), value(data) {};

		Node(const_reference n) { *this = n; };

		reference operator=(const_reference n) {
			if (this != &n) {
				parent = n.parent;
				left = n.left;
				right = n.right;
				value = n.value;
			}
			return *this;
		};

		~Node() {};

		bool operator==(const_reference n) const {
			return (value == n.value);
		};

	};//struct Node

};//namespace ft

#endif