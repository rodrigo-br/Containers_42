#ifndef NODE_H
#define NODE_H

#include "utility.hpp"

namespace ft {

	template<class Pair> struct Node {
		Node				*parent;
		Node				*left;
		Node				*right;
		Pair				value;
		size_t				height;
		typedef Node*		pointer;
		typedef Node&		reference;
		typedef const Node&	const_reference;

		explicit Node() : parent(NULL), left(NULL), right(NULL), height(0) {};

		explicit Node(const Pair &data) : parent(NULL), left(NULL), right(NULL), value(data), height(0) {};

		Node(const_reference n) { *this = n; };

		Node &operator=(const Node& n) {
			if (this != &n) {
				parent = n.parent;
				left = n.left;
				right = n.right;
				value = n.value;
				height = n.height;
			}
			return *this;
		};

		~Node() {};

		pointer leftMost(pointer n) {
			if (n == NULL) { return NULL; }
			while (n->left != NULL) {
				n = n->left;
			}
			return n;
		};

		pointer rightMost(pointer n) {
			if (n == NULL) { return NULL; }
			while (n->right != NULL) {
				n = n->right;
			}
			return n;
		};

		pointer next(pointer n) {
			pointer aux = this;
			if (aux == NULL) { return NULL; }
			if (aux->right != NULL) { return leftMost(aux->right); }
			pointer p = aux->parent;
			while (p != NULL && aux == p->right) {
				aux = p;
				p = p->parent;
			}
			return p;
		};

		pointer prev(pointer n) {
			pointer aux = this;
			if (aux == NULL) { return NULL; }
			if (aux->left != NULL) { return rightMost(aux->left); }
			pointer p = aux->parent;
			while (p != NULL && aux == p->left) {
				aux = p;
				p = p->parent;
			}
			return p;
		};

	};//struct Node

};//namespace ft

#endif