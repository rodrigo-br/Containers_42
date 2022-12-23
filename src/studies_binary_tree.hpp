#ifndef STUDIES_BINARY_TREE_H
#define STUDIES_BINARY_TREE_H

#include "iterator_traits.hpp"
#include "utility.hpp"

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
			void preorder(NodePtr node, Visit) const {};

			template<class Visit>
			void inorder(NodePtr node, Visit) const {};

			template<class Visit>
			void postorder(NodePtr node, Visit) const {};

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

	}; // class TreeBase


}; // namespace ft

#endif