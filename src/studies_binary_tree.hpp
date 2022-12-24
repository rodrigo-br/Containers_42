#ifndef STUDIES_BINARY_TREE_H
#define STUDIES_BINARY_TREE_H

#include "iterator_traits.hpp"
#include "utility.hpp"
#include <memory>

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

			NodePtr newNode(const value_type& value) {
				NodePtr node = _alloc.allocate(1);
				_alloc.construct(node, Node());
				node->value = value;
				node->left = _dummy;
				node->right = _dummy;
				node->parent = _dummy;
				return node;
			};

			NodePtr newNode(const value_type& value, NodePtr p) {
				NodePtr node = _alloc.allocate(1);
				_alloc.construct(node, Node());
				node->value = value;
				node->left = _dummy;
				node->right = _dummy;
				node->parent = p;
				return node;
			};

			NodePtr newNode(ConstNodePtr p) {
				NodePtr node = _alloc.allocate(1);
				_alloc.construct(node, Node());
				node->value = p->value;
				node->left = p->left;
				node->right = p->right;
				node->parent = p->parent;
				return node;
			};

			void deleteNode(NodePtr node) {
				_alloc.destroy(node);
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
			pair<iterator, bool> insertNode(const value_type&) {};

			NodePtr insertLeft(NodePtr node, const value_type&) {};

			NodePtr insertRight(NodePtr node, const value_type&) {};

			static void setParent(NodePtr child, NodePtr parent) {};

			void transferParent(NodePtr x, NodePtr y) {};

			void transferNode(NodePtr x, NodePtr y) {};

			void clear(NodePtr node) {};

			NodePtr copy(ConstNodePtr node) {};

			void copy(const TreeBase &x) {};

			template<class NP> static NP rightMost(NP node) {};

			template<class NP> static NP leftMost(NP node) {};

			static bool isBalanced(ConstNodePtr, size_type &) {};

			static void treeToList(NodePtr node, NodePtr &header) {};

			static NodePtr listToTree(NodePtr header, size_type n) {};

			iterator getIterator(NodePtr node) { return node; };

			NodePtr getNode(iterator it) { return it.current; };


		public:
			TreeBase() : _alloc(allocator_type), _root(NULL), _dummy(newNode()), _size(0) {};

			TreeBase(const TreeBase &x) {};

			TreeBase &operator=(const TreeBase &x) {};

			~TreeBase() {};

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

			pair<iterator, bool> insertUni(const value_type& value) {};

			iterator insertMulti(const value_type& value) {};

			size_type erase(const value_type& value) {};

			void erase(iterator it) {};

			void clear() {};

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