#ifndef RBTREE_H
#define RBTREE_H


#include "Tree.hpp"

/**
 * @brief Como a diferença entre a RBT e a ABP está nos algoritmos de inserção
 * e remoção, a classe RBTree deriva da versão Tree. É necessário, portanto,
 * decorar a estrutura Node com um campo color, que indica a cor do nó,
 * redefinir os métodos públicos de inserção e remoção, especializando-os para
 * a RBT e definir métodos auxiliares que implementam as ações necessárias para
 * a adaptação.
 */
namespace ft {

#define CONTAINER Tree<Key, Value, KeyOfValue, Compare, Alloc>
template <class Key, class Value, class KeyOfValue,
		class Compare = less<Key>,
		class Alloc = std::allocator<Value> >
	class RBTree : public CONTAINER {
		
		public:
			IMPORT_TYPE(iterator);
			IMPORT_TYPE(const_iterator);
			IMPORT_TYPE(size_type);
			IMPORT_TYPE(Node);
			IMPORT_TYPE(NodePtr);
			IMPORT_TYPE(ConstNodePtr);

		protected:
			enum Color { RED, BLACK };
			struct RBNode : public Node {
				Color color;
			};

			typedef typename Alloc::template rebind<RBNode>::other AllocRBNode;
			typedef typename AllocRBNode::pointer RBNodePtr;
			
			AllocRBNode allocRB;

		/*
		*	To avoid using explicit conversions from pointers to RBNodes when
		*	accessing the color of a node, the following set of static methods
		*	are used to access the color of a node from the NodePtr or ConstNodePtr
		*/	
/******************************************************************************/
/*					Color's auxiliar functions							      */
/******************************************************************************/

			static Color getCol(ConstNodePtr node) { return RBNodePtr(node)->color; };

			static void setCol(NodePtr node, Color c) { RBNodePtr(node)->color = c; };

			static void isBlack(ConstNodePtr node) { return getCol(node) == BLACK; };

			static void isRed(ConstNodePtr node) { return getCol(node) == RED; };

			static bool isNullOrBlack(ConstNodePtr node) { return (node == NULL || isBlack(node)); };

		/*
		*	Although the newNode and deleteNode methods are the same as in the
		*	Tree class, they are redefined here to return a RBNodePtr instead.
		* 	This could be avoided using the polymorphism, but it would require
		*	adding a virtual method to the Node class, which would decrease the
		*	performance.
		*/

			void clear(NodePtr node) {
				if (node == NULL) { return; }
				clear(node->left);
				clear(node->right);
				deleteNode(node);
			};

			/**
			 * @brief Aux method that returns a reference to the node pointer
			 * in descendant's way, which value is equal to the argument passed.
			 * 
			 * @param p the argument to be compared
			 * @return NodePtr& 
			 */
			NodePtr &getRefNode(NodePtr p) {
				if (p == CONTAINER::root) { return CONTAINER::root; };
				NodePtr parent = p->parent;
				return (parent->left == p ? parent->left : parent->right);
			}

			void rotateRight(NodePtr p) {};

			void rotateLeft(NodePtr p) {};

			void adjustInsert(NodePtr p) {};

			NodePtr getPrevious(NodePtr p) const {};

			void changeNodes(NodePtr a, NodePtr b) {};

			void eraseInLeaf(NodePtr &r) {};

			void rebalance(NodePtr parent, NodePtr r) {};

			void rebalanceLeft(NodePtr r) {};

			void rebalanceRight(NodePtr r) {};

			static void printOn(std::ostream &os, ConstNodePtr node, int level) {};

		public:
/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

			RBTree(const Compare& comp = Compare(), const Alloc&alloc = Alloc()) :
				CONTAINER(comp, alloc), allocRB(alloc) {};
			
			RBTree(const RBTree& x) : CONTAINER(x.cmp, x.constr), allocRB(x.allocRB) {
				copy(x);
			};

			~RBTree() { clear(); };

			RBTree &operator=(const RBTree& x) {
				if (this != &x) {
					clear();
					copy(x);
				}
				return *this;
			};

			void clear() {
				clear(CONTAINER::root);
				CONTAINER::dummy->left = CONTAINER::dummy->right = CONTAINER::dummy;
				CONTAINER::root = NULL;
				CONTAINER::_size = 0;
			};

			void printOn(std::ostream &os) const { printOn(os, CONTAINER::root, 1); };

			NodePtr newNode(NodePtr p, const Value& val) {};

			NodePtr newNode(ConstNodePtr p) {};

			void deleteNode(NodePtr p) {};

			template<bool, MULTI>
			pair <iterator, bool> insertNode(const Value& val) {};

			NodePtr insertLeft(NodePtr r, const Value& val) {};

			NodePtr insertRight(NodePtr r, const Value& val) {};

			bool erase(const Key& k) {};

			void erase(iterator it) {};


	};// class RBTree
	#undef CONTAINER

};// namespace ft

#endif