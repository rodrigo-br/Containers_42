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

			/**
			 * @brief Methods that rotate the tree to left or right uses the actions
			 * ilustrated in the image below:
			 * https://drive.google.com/file/d/1ZVv0_qj78NOV_p7dT-cc_Jn9xinSQF7I/view?usp=sharing
			 * 
			 */
			void rotateRight(NodePtr m) {
				NodePtr &rp = getRefNode(m);
				rp = m->left;
				m->left = rp->right;
				rp->right = m;
				if (m->left != NULL)
					m->left->parent = m;
				rp->parent = m->parent;
				m->parent = rp;
			};

			/**
			 * @brief Methods that rotate the tree to left or right uses the actions
			 * ilustrated in the image below:
			 * https://drive.google.com/file/d/1ZVv0_qj78NOV_p7dT-cc_Jn9xinSQF7I/view?usp=sharing
			 * 
			 * Although the image is the same, the methods are just a simetric reflection
			 * of the other.
			 */
			void rotateLeft(NodePtr n) {
				NodePtr &rp getRefNode(n);
				rp = n->right;
				n->right = rp->left;
				rp->left = n;
				if (n->right != NULL)
					n->right->parent = n;
				rp->parent = n->parent;
				n->parent = rp;
			};

			/**
			 * @brief The insert methods in the RBT follow the same logic as in
			 * the Tree class, but they also have to colors the node and adjust
			 * the tree to keep the RBT properties.
			 * 
			 * This method is an auxiliar method to the insert methods as
			 * ilustrated in the image below:
			 * https://drive.google.com/file/d/1PoTdN-kQ6s3DTJoyYqcLkt8smtk78Qov/view?usp=sharing
			 */
			void adjustInsert(NodePtr r) {
				if (r == CONTAINER::root) {
					setCol(r, BLACK); //Case 1)
					return;
				}
				if (isBlack(r->parent)) { 
					return; //Case 2 and 3)
				}
				NodePtr gramma = r->parent->parent;
				NodePtr p_right = gramma->right;
				NodePtr p_left = gramma->left;
				if /*if 1*/(isNullOrBlack(p_left) || isNullOrBlack(p_right)) {
					if /*if 2*/(isNullOrBlack(p_left)) {
						if (p_right->left == r)
							rotateRight(p_right); //Case 4)
						rotateLeft(gramma); //Case 5)
					} /*endif 2*/else {
						if (p_left->right == r)
							rotateLeft(p_left); //Case 6)
						rotateRight(gramma); //Case 7)
					}
				setCol(gramma, RED);
				setCol(gramma->parent, BLACK);
				}/*endif 1*/ else { //Case 8, 9, 10 and 11)
					setCol(p_left, BLACK);
					setCol(p_right, BLACK);
					if /*if 3*/ (gramma != CONTAINER::root) {
						setCol(gramma, RED);
						adjustInsert(gramma);
					} /*endif 3*/
				}/*endelse do if 1*/
			};

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

			/**
			 * @brief If the node doesn't exist, it adjust the insertion.
			 */
			pair <iterator, bool> insertUni(const Value& val) {
				pair<iterator, bool> res = insertNode<false>(val);
				if (res.second)
					adjustInsert(getNode(res.first));
				return res;
			};

			/**
			 * @brief always need to adjust the insertion. 
			 */
			iterator insertMulti(const Value& val) {
				iterator res = insertNode<true>(val).first;
				adjustInsert(getNode(res));
				return res;
			};

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