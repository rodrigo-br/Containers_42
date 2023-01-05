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
		public:
		typedef BSTree 											bst_type;
		typedef BSTree& 										bst_reference;
		typedef T 												value_type;
		typedef Node 											node_type;
		typedef Node* 											node_pointer;
		typedef size_t											size_type;
		typedef ft::bidirectional_iterator<Node, Compare> 		iterator;
		typedef ft::const_bidirectional_iterator<Node, Compare> const_iterator;

		node_pointer		tail;
		Node_Alloc			node_alloc;

		BSTree(const Node_Alloc& alloc = Node_Alloc()) : node_alloc(alloc) {
			tail = node_alloc.allocate(1);
			node_alloc.construct(tail, Node(tail, tail, tail));
		};

		void simple_destroy(node_pointer &node, size_t val) {
			node_alloc.destroy(node);
			node_alloc.deallocate(node, val);
		}

		~BSTree() {
			simple_destroy(tail, 1);
		};

		ft::pair<iterator bool> insertPair(value_type to_insert) {
			node_pointer new_node = node_alloc.allocate(1);
			node_pointer prev_node = tail;
			node_pointer begin = tail->parent;
			bool is_left = true;

			while (begin != tail) {
				int current_key = begin->value.first;
				if (current_key == to_insert.first)
					return (ft::make_pair(iterator(begin, tail), false));
				prev_node = begin;
				if (to_insert.first > current_key) {
					is_left = true;
					begin = begin->right;
				} else {
					is_left = false;
					begin = begin->left;
				}
			}
			node_alloc.construct(new_node, Node(to_insert, prev_node, tail, tail));
			if (prev_node == tail) {
				tail->parent = new_node;
			} else if (is_left) {
				prev_node->right = new_node;
			} else {
				prev_node->left = new_node;
			}
			updateTail(1);
			return (ft::make_pair(iterator(new_node, tail), true));
		};

		void updateTail(int val) {
			tail->left = leftMost(tail->parent);
			tail->right = rightMost(tail->parent);
			tail->value.first += val;
		};

		node_pointer leftMost(node_pointer node) {
			while (node != tail && node->left != tail)
				node = node->left;
			return node;
		};

		node_pointer rightMost(node_pointer node) {
			while (node != tail && node->right != tail)
				node = node->right;
			return node;
		};

		void remove(value_type val) { remove(tail->parent, val) };

		void remove(node_pointer node, value_type val) {
			if (val.first < node->value.first) {
				remove(node->left, val);
				return;
			}
			if (val.first > node->value.first) {
				remove(node->right, val);
				return;
			}
			if (node->left != tail && node->right != tail) {
				node_pointer suc = leftMost(node->right);
				replaceDoubleChildren(node, suc);
				return;
			}
			else if (node->left != tail) { replaceNodeInParent(node, node->left); }
			else if (node->right != tail) { replaceNodeInParent(node, node->right); }
			else { replaceNodeInParent(node, tail); }
		};

		void replaceNodeInParent(node_pointer node, node_pointer new_node) {
			if (node->parent == tail) {
				tail->parent = new_node;
			}
			else {
				if (tail->parent == node)
					tail->parent = new_node;
				if (node == node->parent->left)
					node->parent->left = new_node;
				else
					node->parent->right = new_node;
			}
			updateTail(-1);
			new_node->parent = node->parent;
			simple_destroy(node, 1);
		};

		void replaceDoubleChildren(node_pointer &node, node_pointer new_node) {
			if (new_node->parent != tail && new_node->parent != node)
				new_node->parent->left = new_node->right;
			new_node->parent = node->parent;
			if (node->left != new_node)
				new_node->left = node->left;
			if (node->right != new_node)
				new_node->right = node->right;
			if (node->parent == tail) {
				if (node->parent->left == node)
					node->parent->left = new_node;
				else if (node->parent->right == node)
					node->parent->right = new_node;
			}
			else 
				tail->parent = new_node;
			if (node->left != tail && node->left != new_node)
				node->left->parent = new_node;
			if (node->right != tail && node->right != new_node)
				node->right->parent = new_node;
			if (node->parent != tail) {
				node->left = tail;
				node->right = tail;
				node->parent = new_node;
			}
			updateTail(-1);
			simple_destroy(node, 1);
		};
		
		node_pointer search(value_type node) {
			node_pointer begin = tail->parent;
			while (begin != tail) {
				if (begin->value.first == node.first) { return begin; }
				if (begin->value.first > node.first) { begin = begin->left; }
				else { begin = begin->right; }
			}
			return begin;
		};

		void swap(bst_reference other) {
			if (this != &other)
				std::swap(tail, other.tail);
		};

		size_type max_size() const { return node_alloc.max_size(); };

	};//class Tree

};//namespace ft

#endif