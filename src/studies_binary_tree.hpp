#ifndef STUDIES_BINARY_TREE_H
#define STUDIES_BINARY_TREE_H

#include "iterator_traits.hpp"
#include "utility.hpp"
#include <memory>
#include <iostream>

namespace ft {
	template<class T, class Alloc = std::allocator<T> >
	class TreeBase {

		protected:
			struct Node;
			typedef typename Alloc::template rebind<Node>::other	ANode;
			typedef typename ANode::pointer 						NodePtr;
			typedef typename ANode::const_pointer 					ConstNodePtr;
			struct Node {
				T			value;
				NodePtr		left;
				NodePtr		right;
				NodePtr		parent;
			};
			template<class NodePtr, class Ptr, class Ref> class IT;

		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename Alloc::reference					reference;
			typedef typename Alloc::const_reference				const_reference;
			typedef typename Alloc::pointer						pointer;
			typedef typename Alloc::const_pointer				const_pointer;
			typedef typename Alloc::difference_type				difference_type;
			typedef typename Alloc::size_type					size_type;
			typedef IT<NodePtr, pointer, reference>				iterator;
			typedef IT<
			ConstNodePtr, const_pointer, const_reference>		const_iterator;
		
		
		protected:
			ANode		_alloc;
			NodePtr		_root;
			NodePtr		_dummy;
			size_type	_size;

			NodePtr newNode() {
				NodePtr n = _alloc.allocate(1);
				return n->left = n->right = n->parent = n;
			};

			NodePtr newNode(NodePtr parent, const value_type& value) {
				NodePtr n = _alloc.allocate(1);
				_alloc.construct(&(n->value), value);
				n->left = n->right = NULL;
				n->parent = parent;
				return n;
			};

			NodePtr newNode(ConstNodePtr x) {
				NodePtr n = _alloc.allocate(1);
				_alloc.construct(&(n->value), x->value);
				return n;
			};

			void deleteNode(NodePtr node) {
				_alloc.destroy(&(node->value));
				_alloc.deallocate(node, 1);
			};

			template<class Visit>
			void preorder(NodePtr node, Visit visit) const {
				if (node == NULL)
					return;
				visit(node->value);
				preorder(node->left, visit);
				preorder(node->right, visit);
			};

			template<class Visit>
			void inorder(NodePtr node, Visit visit) const {
				if (node == NULL)
					return;
				inorder(node->left, visit);
				visit(node->value);
				inorder(node->right, visit);
			};

			template<class Visit>
			void postorder(NodePtr node, Visit visit) const {
				if (node == NULL)
					return;
				inorder(node->left, visit);
				inorder(node->right, visit);
				visit(node->value);
			};

			template<bool MULTI>
			pair<iterator, bool> insertNode(const value_type& value) {
				NodePtr r;
				if (_root == NULL) {
					r = _root = _dummy->left = _dummy->right = newNode(_dummy, value);
				}
				else {
					r = _root;
					for (;;) {
						if (value < r->value) {
							if (r->left == NULL) {
								r = insertLeft(r, value);
								break;
							}
							r = r->left;
						}
						else if (MULTI || value > r->value) {
							if (r->right == NULL) {
								r = insertRight(r, value);
								break;
							}
							r = r->right;
						}
						else {
							return pair<iterator, bool>(r, false);
						}
					}
				}
				++_size;
				return pair<iterator, bool>(r, true);
			};

			NodePtr insertLeft(NodePtr node, const value_type& value) {
				node->left = newNode(node, value);
				if (node == _dummy->left)
					_dummy->left = node->left;
				return node->left;
			};

			NodePtr insertRight(NodePtr node, const value_type& value) {
				node->right = newNode(node, value);
				if (node == _dummy->right)
					_dummy->right = node->right;
				return node->right;
			};

			static void setParent(NodePtr child, NodePtr parent) {
				if (child != NULL)
					child->parent = parent;
			};

			void transferParent(NodePtr x, NodePtr y) {
				NodePtr xp = x->parent;
				((x == root) ? root : (xp->right == x) ? xp->right : xp->left) = y;
				setParent(y, xp);
			};

			void transferNode(NodePtr x, NodePtr y) {
				transferParent(x, y);
				y->left = x->left;
				setParent(y->left, y);
				y->right = x->right;
				setParent(y->right, y);
			};

			void clear(NodePtr node) {
				if (node == NULL)
					return;
				clear(node->left);
				clear(node->right);
				deleteNode(node);
			};

			NodePtr copy(ConstNodePtr node) {
				if (node == NULL)
					return NULL;
				NodePtr r = newNode(node);
				r->left = copy(node->left);
				setParent(r->left, r);
				r->right = copy(node->right);
				setParent(r->right, r);
				return r;
			};

			void copy(const TreeBase &x) {
				if (x.empty()) { return; }
				_root = copy(x._root);
				_root->parent = _dummy;
				_dummy->left = leftMost(_root);
				_dummy->right = rightMost(_root);
				_size = x.size();
			};

			template<class NP> static NP rightMost(NP node) {
				while (node->right != NULL)
					node = node->right;
				return node;
			};

			template<class NP> static NP leftMost(NP node) {
				while (node->left != NULL)
					node = node->left;
				return node;
			};

			static bool isBalanced(ConstNodePtr, size_type &) {};

			static void treeToList(NodePtr node, NodePtr &header) {};

			static NodePtr listToTree(NodePtr header, size_type n) {};

			iterator getIterator(NodePtr node) { return node; };

			NodePtr getNode(iterator it) { return it.current; };


		public:
			TreeBase(const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _root(NULL), _dummy(newNode()), _size(0) {};

			TreeBase(const TreeBase &x) :
				_alloc(x.get_allocator()), _root(NULL), _dummy(newNode()), _size(0) {
				copy(x);
			};

			TreeBase &operator=(const TreeBase &x) {
				if (this != &x) {
					clear();
					copy(x);
				}
				return *this;
			};

			~TreeBase() {
				clear(_root);
				_alloc.deallocate(_dummy, 1);
			};

			allocator_type get_allocator() const { return _alloc; };

			template<class Visit>
			void preorder(Visit visit) const { preorder(_root, visit); };

			template<class Visit>
			void inorder(Visit visit) const { inorder(_root, visit); };

			template<class Visit>
			void postorder(Visit visit) const { postorder(_root, visit); };

			iterator begin() { return _dummy->left; };

			const_iterator begin() const { return _dummy->left; };

			iterator end() { return _dummy; };

			const_iterator end() const { return _dummy; };

			size_type size() const { return _size; };

			bool empty() const { return _size == 0; };

			reference front() { return *begin(); };

			reference back() { return *--end(); };

			const_reference front() const { return *begin(); };

			const_reference back() const { return *--end(); };

			iterator find(const value_type& value) {
				NodePtr node = _root;
				aux = _dummy;
				while (node != NULL) {
					if (node->value < value)
						node = node->right;
					else {
						aux = node;
						node = node->left;
					}
				}
				return (aux == _dummy || value < aux->value) ? end() : aux;
			};

			pair<iterator, bool> insertUni(const value_type& value) {
				return insertNode<false>(value);
			};

			iterator insertMulti(const value_type& value) {
				return insertNode<true>(value).first;
			};

			size_type erase(const value_type& value) {
				size_type count = 0;
				iterator p = find(value);
				if (p != end()) {
					do {
						++count; erase(p++);
					} 
					while {
						p != end() && !(value < *p);
					}
				}
				return count;
			};

			void erase(iterator it) {
				NodePtr r = it.current;
				if (r == _dummy->left) { _dummy->left = (++iterator(it).current); }
				if (r == _dummy->right) { _dummy->right = (--iterator(it).current); }
				if (r->left == NULL) { transferParent(r, r->right); }
				else if (r->right == NULL) { transferParent(r, r->left); }
				else {
					NodePtr previous = rightMost(r->left);
					transferParent(previous, previous->left);
					transferNode(r, previous);
				}
				--_size;
				deleteNode(r);
			};

			void clear() {
				clear(_root);
				_dummy->left = _dummy->right = _dummy;
				_root = NULL;
				_size = 0;
			};

			void balance() {};

			void displayValue(const value_type& value) const {
				std::cout << value << ' ';
			};

			void display() const {
				inorder(displayValue());
			};

			bool isBalanced() const {};

			bool isOrdered() const {};

			void printOn(ostream &os) const {};

	}; // class TreeBase


}; // namespace ft

#endif