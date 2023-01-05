#ifndef TREE_H
#define TREE_H

#include "bidirectional_iterator.hpp"
#include <functional>

namespace ft {

template <class T,
		class Compare = std::less<T>,
		class Node = ft::Node<T>,
		class T_Alloc = std::allocator<T>,
		class Node_Alloc = std::allocator<Node> >
	class BSTree {

		typedef BSTree 											bst_type;
		typedef BSTree& 										bst_reference;
		typedef T 												value_type;
		typedef Node 											node_type;
		typedef Node* 											node_pointer;
		typedef size_t											size_type;
		typedef ft::bidirectional_iterator<Node, Compare> 		iterator;
		typedef ft::const_bidirectional_iterator<Node, Compare> const_iterator;

	};//class Tree

};//namespace ft

#endif