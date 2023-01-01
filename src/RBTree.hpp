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
template <class Key, class Value,
		class KeyOfValue = ft::Identity<Key, Value>,
		class Compare = less<Key>,
		class Alloc = std::allocator<Value> >
	class RBTree : public CONTAINER {
		
		public:
			IMPORT_TYPE(iterator);
			IMPORT_TYPE(const_iterator);
			IMPORT_TYPE(size_type);
			IMPORT_TYPE(Node);
			IMPORT_TYPE(NodePtr);
			struct RBNode;
			typedef typename Alloc::template rebind<RBNode>::other AllocRBNode;
			typedef typename AllocRBNode::pointer RBNodePtr;
			
			AllocRBNode allocRB;
			IMPORT_TYPE(ConstNodePtr);
			enum Color { RED, BLACK };
			struct RBNode : public Node {
				Color color;
			};

		protected:
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

			static bool isBlack(ConstNodePtr node) { return getCol(node) == BLACK; };

			static bool isRed(ConstNodePtr node) { return getCol(node) == RED; };

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
				NodePtr &rp = getRefNode(n);
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

			NodePtr getPrevious(NodePtr p) const { return CONTAINER::rightMost(p->left); };

			void changeNodes(NodePtr x, NodePtr y) {
				NodePtr yp = y->parent;
				NodePtr xl = x->left;
				getRefNode(x) = y;
				y->parent = x->parent;
				x->left = y->left;
				if (x->left != NULL)
					x->left->parent = x;
				y->right = x->right;
				y->right->parent = y;
				if (xl != y) {
					yp->right = x;
					x->parent = yp;
				}
				else
					xl = x;
				y->left = xl;
				xl->parent = y;
				x->right = NULL;
				Color c = getCol(x);
				setCol(x, getCol(y));
				setCol(y, c);
			};

			void eraseInLeaf(NodePtr &r) {
				if (isRed(r) || CONTAINER::size() == 1) {
					deleteNode(r);
					r = NULL;
					return ;
				}
				if (!isNullOrBlack(r->right) || !isNullOrBlack(r->left)) {
					NodePtr rem = r;
					if (isNullOrBlack(r->left))
						r = r->right;
					else
						r = r->left;
					r->parent = rem->parent;
					deleteNode(rem);
					setCol(r, BLACK);
				} else {
					NodePtr parent = r->parent;
					deleteNode(r);
					r = NULL;
					rebalance(parent, NULL);
				}
			};

			void rebalance(NodePtr parent, NodePtr r) {
				if (r == NULL)
					return ;
				if (parent->left == r)
					rebalanceLeft(parent);
				else
					rebalanceRight(parent);
			};

			void rebalanceLeft(NodePtr r) {
				NodePtr pr = r->right;
				if (isRed(pr)) {
					rotateLeft(r);
					setCol(pr, BLACK);
					setCol(r, RED);
					pr = r->right;
				}
				if (isNullOrBlack(pr->left) && isNullOrBlack(pr->right)) {
					setCol(pr, RED);
					if (isRed(r))
						setCol(r, BLACK);
					else
						rebalance(r->parent, r);
				} else {
					if (isNullOrBlack(pr->right))
						rotateRight(pr);
					rotateLeft(r);
					setCol(r->parent, getCol(r));
					setCol(r->parent->right, BLACK);
					setCol(r, BLACK);
				}
			};

			void rebalanceRight(NodePtr r) {
				NodePtr pl = r->left;
				if (isRed(pl)) {
					rotateRight(r);
					setCol(pl, BLACK);
					setCol(r, RED);
					pl = r->left;
				}
				if (isNullOrBlack(pl->left) && isNullOrBlack(pl->right)) {
					setCol(pl, RED);
					if (isRed(r))
						setCol(r, BLACK);
					else
						rebalance(r->parent, r);
				} else {
					if (isNullOrBlack(pl->left)) {
						rotateLeft(pl);
					}
					rotateRight(r);
					setCol(r->parent, getCol(r));
					setCol(r->parent->left, BLACK);
					setCol(r, BLACK);
				}
			};

			/**
			 * @brief print the tree on the given stream from left to right
			 * (NOT FROM TOP TO BOTTOM)
			 */
			static void printOn(std::ostream &os, ConstNodePtr node, int level) {
				if (node == NULL)
					return ;
				printOn(os, node->left, level + 1);
				for (int i = 0; i < level; i++)
					os << "\t";
				if (RBNodePtr(node)->color == RED)
					os << "\033[1m\033[31m " << node->value << "\033[0m" << std::endl;
				else
					os << "\033[1m\033[30m" << node->value << "\033[0m" << std::endl;
				printOn(os, node->right, level + 1);
			};

		public:
/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

			RBTree(const Compare& comp = Compare(), const Alloc&a = Alloc()) :
				CONTAINER(comp, a), allocRB(a) {};
			
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

			/**
			 * @brief Auxiliar function to print the tree on the given stream
			 * from left to right (NOT FROM TOP TO BOTTOM).
			 * it calls the static function printOn recursively.
			 */
			void printOn(std::ostream &os) const { printOn(os, CONTAINER::root, 1); };

			/**
			 * @brief The difference between the newNode from Tree and RBTree 
			 * is that allocate and deallocate invoke the RBNode object trough
			 * the allocRB allocator and it initialize the attributes color. 
			 */
			NodePtr newNode(NodePtr p, const Value& val) {
				NodePtr n = allocRB.allocate(1);
				CONTAINER::constr.construct(&(n->value), val);
				n->left = n->right = NULL;
				n->parent = p;
				setCol(n, RED);
				return n;
			};

			NodePtr newNode(ConstNodePtr p) {
				NodePtr n = allocRB.allocate(1);
				CONTAINER::constr.construct(&(n->value), p->value);
				setCol(n, getCol(p));
				return n;
			};

			/**
			 * @brief destroy through constr and deallocate through allocRB.
			 */
			void deleteNode(NodePtr p) {
				CONTAINER::constr.destroy(&(p->value));
				allocRB.deallocate(RBNodePtr(p), 1);
			};

			/**
			 * @brief If the node doesn't exist, it adjust the insertion.
			 */
			pair <iterator, bool> insertUni(const Value& val) {
				pair<iterator, bool> res = insertNode<false>(val);
				if (res.second)
					adjustInsert(CONTAINER::getNode(res.first));
				return res;
			};

			/**
			 * @brief always need to adjust the insertion. 
			 */
			iterator insertMulti(const Value& val) {
				iterator res = insertNode<true>(val).first;
				adjustInsert(CONTAINER::getNode(res));
				return res;
			};

			/**
			 * @brief Exactly same implementation as Tree
			 */
			template<bool MULTI>
			pair <iterator, bool> insertNode(const Value& v) {
				NodePtr node;
					if (CONTAINER::root == NULL)
						node = CONTAINER::root = CONTAINER::dummy->left = CONTAINER::dummy->right = CONTAINER::newNode(CONTAINER::dummy, v);
					else {
						node = CONTAINER::root;
						for (;;) {
							if (CONTAINER::cmp(CONTAINER::key(v), CONTAINER::key(node->value))) {
								if (node->left != NULL)
									node = node->left;
								else {
									node = CONTAINER::insertLeft(node, v);
									break ;
								}
							} else if (MULTI || CONTAINER::cmp(CONTAINER::key(node->value), CONTAINER::key(v))) {
								if (node->right != NULL)
									node = node->right;
								else {
									node = CONTAINER::insertRight(node, v);
									break ;
								}
							} else
								return pair<iterator, bool>(CONTAINER::getIterator(node), false);
							}
						}
					CONTAINER::_size++;
					return pair<iterator, bool>(CONTAINER::getIterator(node), true);
			};

			NodePtr insertLeft(NodePtr node, const Value& value) {
				node->left = newNode(node, value);
				if (node == CONTAINER::dummy->left)
					CONTAINER::dummy->left = node->left;
				return node->left;
			};

			NodePtr insertRight(NodePtr node, const Value& value) {
				node->right = newNode(node, value);
				if (node == CONTAINER::dummy->right)
					CONTAINER::dummy->right = node->right;
				return node->right;
			};

			bool erase(const Key& k) {
				iterator p = find(k);
					size_type count = 0;
					if (p != CONTAINER::end()) {
						do {
							erase(p++);
							count++;
						} while (p != CONTAINER::end() && !cmp(k, key(*p)));
					}
					return count;
			};

			void erase(iterator it) {
				NodePtr p = CONTAINER::getNode(it);
				if (p == CONTAINER::dummy->left)
					CONTAINER::dummy->left = CONTAINER::getNode(++iterator(it));
				if (p == CONTAINER::dummy->right)
					CONTAINER::dummy->right = CONTAINER::getNode(--iterator(it));
				if (p->left != NULL && p->right != NULL)
					changeNodes(p, CONTAINER::rightMost(p->left));
				eraseInLeaf(getRefNode(p));
				--CONTAINER::_size;
			};


	};// class RBTree
	#undef CONTAINER

};// namespace ft

#endif