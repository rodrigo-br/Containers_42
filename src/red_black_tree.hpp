#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <memory>
namespace ft {

enum RBTreeColor { RED = false, BLACK = true};

struct RBTreeBaseNode {

	typedef RBTreeBaseNode*			BasePtr;
	typedef const RBTreeBaseNode*	ConstBasePtr;

	BasePtr							parent;
	BasePtr							left;
	BasePtr							right;
	RBTreeColor						color;

	static BasePtr		minimum(BasePtr x) {
		while (x->left != 0)
			x = x->left;
		return x;
	};

	static BasePtr		maximum(BasePtr x) {
		while (x->right != 0)
			x = x->right;
		return x;
	};

	static ConstBasePtr	minimum(ConstBasePtr x) {
		while (x->left != 0)
			x = x->left;
		return x;
	};

	static ConstBasePtr	maximum(ConstBasePtr x) {
		while (x->right != 0)
			x = x->right;
		return x;
	};

};// struct RBTreeBaseNode

template <typename key_compare>
struct RBTreeKeyCompare {

	key_compare		comp;


	RBTreeKeyCompare(key_compare c) : comp(c) {}

};// struct RBTreeKeyCompare


template <class Key, class Value, class KeyOfValue, class Compare,
	class Alloc = std::allocator<Value> >
class RBTree {



};// class RBTree

};// namespace ft

#endif