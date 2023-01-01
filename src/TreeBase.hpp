#ifndef TREEBASE_H
#define TREEBASE_H

/*
	Tree - Árvore é a coleção de nó cuja posição e informação contida satisfazzem um
	um determinado conjunto de propriedades

	Node - Nós são os objetos que compõem a coleção

	-> Ramos são as ligações entre os nós

	Root - Raiz é o nó de onde emerge, direta ou indiretamente, todos os outros nós.
	A raiz não possui ascendentes.

	Leaf - Folhas são os nós que não possuem descendentes

	Percurso é um caminho possível entre dois nós distintos, satisfazendo 
	uma determinada condição

	Nível de um nó é a distância entre ele e a raiz

	Altura de uma árvore é o máximo nível onde se situa um nó.

	Parent - Ascendente (ou pai) é o nó que está acima de outro nó. É o nó mais próximo
	da raiz ao qual esse nó está ligado

	left/right - Descendente (ou filho) é o nó que está abaixo de outro nó. É o nó mais
	próximo da folha ao qual esse nó está ligado.
*/

#include <memory>
#include "Container.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include "bidirectional_iterator.hpp"
#include <cmath>

namespace ft {
#define CONTAINER ft::Container<T, Alloc>
	template<class T, class Alloc = std::allocator<T> >
	class TreeBase : public CONTAINER {

		public:
			IMPORT_TYPE(value_type);
			IMPORT_TYPE(allocator_type);
			IMPORT_TYPE(reference);
			IMPORT_TYPE(const_reference);
			IMPORT_TYPE(pointer);
			IMPORT_TYPE(const_pointer);
			IMPORT_TYPE(size_type);
			IMPORT_TYPE(difference_type);
			struct													Node;
			typedef typename Alloc::template rebind<Node>::other 	ANode;
			typedef typename ANode::pointer							NodePtr;
			typedef typename ANode::const_pointer					ConstNodePtr;
			struct Node {
				value_type	value;
				NodePtr		parent;
				NodePtr		left;
				NodePtr		right;
			};

		protected:
			ANode			alloc;
			allocator_type	constr;
			size_type		_size;
			NodePtr			root;
			NodePtr			dummy;

		public:
			typedef ft::bidirectional_iterator<NodePtr>				iterator;
			typedef ft::bidirectional_iterator<ConstNodePtr>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

			TreeBase(const allocator_type &a = allocator_type()) :
				alloc(a), constr(a), _size(0), root(NULL), dummy(newNode()) {};
			
			TreeBase(const TreeBase &x) :
				constr(x.get_allocator()), alloc(x.get_allocator()), root(NULL), _size(0), dummy(newNode()) {
					copy(x);
				};

			~TreeBase() {
				clear(root);
				alloc.deallocate(dummy, 1);
			};

			TreeBase &operator=(const TreeBase &x) {
				if (this != &x) {
					clear();
					copy(x);
				}
				return *this;
			};

			NodePtr newNode() {
				NodePtr node = alloc.allocate(1);
				return node->left = node->right = node->parent = node;
			};

			NodePtr newNode(NodePtr parent, const value_type &value) {
				NodePtr node = alloc.allocate(1);
				constr.construct(&node->value, value);
				node->left = node->right = NULL;
				node->parent = parent;
				return node;
			};

			NodePtr newNode(ConstNodePtr parent) {
				NodePtr node = alloc.allocate(1);
				constr.construct(&(node->value), parent->value);
				return node;
			};

			void deleteNode(NodePtr node) {
				constr.destroy(&(node->value));
				alloc.deallocate(node, 1);
			};

/******************************************************************************/
/*					Percursos pre, in, post								      */
/******************************************************************************/

			template<class Visit> void preorder(NodePtr node, Visit visit) const {
				if (node == NULL) { return; };
				visit(node->value);
				preorder(node->left, visit);
				preorder(node->right, visit);
			};

			template<class Visit> void inorder(NodePtr node, Visit visit) const {
				if (node == NULL) { return; };
				inorder(node->left, visit);
				visit(node->value);
				inorder(node->right, visit);
			};

			template<class Visit> void postorder(NodePtr node, Visit visit) const {
				if (node == NULL) { return; };
				inorder(node->left, visit);
				inorder(node->right, visit);
				visit(node->value);
			};

			template<class Visit> void preorder(Visit visit) const { preorder(root, visit); };

			template<class Visit> void inorder(Visit visit) const { inorder(root, visit); };

			template<class Visit> void postorder(Visit visit) const { postorder(root, visit); };


/******************************************************************************/
/*						Modifiers										      */
/******************************************************************************/

			pair<iterator, bool> insertUni(const value_type &value) {
				return insertNode<false>(value);
			};

			iterator insertMulti(const value_type &value) {
				return insertNode<true>(value).first;
			};

			template<bool MULTI> pair<iterator, bool> insertNode(const value_type &value) {
				NodePtr node;
				if (root == NULL)
					node = root = dummy->left = dummy->right = newNode(dummy, value);
				else {
					node = root;
					for (;;) {
						if (value < node->value) {
							if (node->left != NULL)
								node = node->left;
							else {
								node = insertLeft(node, value);
								break;
							}
						} else if (MULTI || value > node->value) {
							if (node->right != NULL)
								node = node->right;
							else {
								node = insertRight(node, value);
								break;
							}
						} else
							return pair<iterator, bool>(iterator(node), false);
					}
				}
				++_size;
				return pair<iterator, bool>(iterator(node), true);
			};

			NodePtr insertLeft(NodePtr node, const value_type &value) {
				node->left = newNode(node, value);
				if (node == dummy->left)
					dummy->left = node->left;
				return node->left;
			};

			NodePtr insertRight(NodePtr node, const value_type &value) {
				node->right = newNode(node, value);
				if (node == dummy->right)
					dummy->right = node->right;
				return node->right;
			};

			static void setParent(NodePtr child, NodePtr parent) {
				if (child != NULL)
					child->parent = parent;
			};

			void transferParent(NodePtr x, NodePtr y) {
				NodePtr xp = x->parent;
				((x==root) ? root : (xp->right == x) ? xp->right : xp->left) = y;
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
				if (node == NULL) { return; };
				clear(node->left);
				clear(node->right);
				deleteNode(node);
			};

			NodePtr copy(ConstNodePtr node) {
				if (node == NULL) { return NULL; };
				NodePtr r = newNode(node);
				r->left = copy(node->left);
				setParent(r->left, r);
				r->right = copy(node->right);
				setParent(r->right, r);
				return r;
			};

			void copy(const TreeBase &x) {
				if (x.empty()) { return; };
				root = copy(x.root);
				root->parent = dummy;
				dummy->left = leftMost(root);
				dummy->right = rightMost(root);
				_size = x.size();
			};

			static void treeToList(NodePtr node, NodePtr &head) {
				if (node == NULL) { return; };
				treeToList(node->right, head);
				node->right = head;
				head = node;
				treeToList(node->left, head);
			};

			static NodePtr listToTree(NodePtr &head, size_type size) {
				if (size == 0) { return NULL; };
				int half = size / 2;
				NodePtr left = listToTree(head, half);
				NodePtr root = head;
				head = head->right;
				root->left = left;
				setParent(root->left, root);
				root->right = listToTree(head, size - 1 - half);
				setParent(root->right, root);
				return root;
			};

			size_type erase(const value_type &value) {
				size_type count = 0;
				iterator p = find(value);
				if (p != end()) {
					do {
						erase(p++);
						++count;
					} while (p != end() && value < *p);
				}
				return count;
			};

			void erase(iterator i) {
				NodePtr node = i.base();
				if (node == dummy->left)
					dummy->left = (++iterator(i).base());
				if (node == dummy->right)
					dummy->right = (--iterator(i).base());
				if (node->left == NULL)
					transferParent(node, node->right);
				else if (node->right == NULL)
					transferParent(node, node->left);
				else {
					NodePtr previous = rightMost(node->left);
					transferParent(previous, previous->left);
					transferNode(node, previous);
				}
				--_size;
				deleteNode(node);
			};

			void clear() {
				clear(root);
				dummy->left = dummy->right = dummy;
				root = NULL;
				_size = 0;
			};

			void balance() {
				if (size() <= 2) { return ; }
				NodePtr head = NULL;
				treeToList(root, head);
				root = listToTree(head, size());
				root->parent = dummy;
			};

/******************************************************************************/
/*						Getters											      */
/******************************************************************************/

			iterator getIterator(NodePtr node) { return iterator(node); };

			NodePtr getNode(iterator i) { return i.base(); };

			allocator_type get_allocator() const { return constr; };

			size_type size() const { return _size; };

			bool empty() const { return size() == 0; };

/******************************************************************************/
/*						Iterators										      */
/******************************************************************************/

			iterator begin() { return iterator(dummy->left); };

			iterator end() { return iterator(dummy); };

			const_iterator begin() const { return const_iterator(dummy->left); };

			const_iterator end() const { return const_iterator(dummy); };

			reverse_iterator rbegin(void) {	return reverse_iterator(end()); };

			const_reverse_iterator rbegin(void) const {	return const_reverse_iterator(end()); };

			reverse_iterator rend(void) { return reverse_iterator(begin()); };

			const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); };

/******************************************************************************/
/*						Acessors										      */
/******************************************************************************/

			reference front() { return *begin(); };

			reference back() { return *(--end()); };

			const_reference front() const { return *begin(); };

			const_reference back() const { return *(--end()); };

			iterator find(const T &value) {
				NodePtr node = root;
				NodePtr aux = dummy;
				while (node != NULL) {
					if (node->value < value)
						node = node->right;
					else {
						aux = node;
						node = node->left;
					} 
				}
				return (aux == dummy || value < aux->value) ? end() : iterator(aux);
			};

			template<class NP>
			NP leftMost(NP node) {
				while (node->left != NULL) {
					node = node->left;
				}
				return node;
			};

			template<class NP>
			NP rightMost(NP node) {
				while (node->right != NULL) {
					node = node->right;
				}
				return node;
			};

/******************************************************************************/
/*						Debugger										      */
/******************************************************************************/

			bool isOrded() const;

			bool isBalanced() const {
				int height;
				return isBalanced(root, height);
			};

			bool isBalanced(NodePtr node, int &height) const {
				if (node == NULL) {
					height = 0;
					return true;
				}
				int leftHeight;
				if (isBalanced(node->right, height) && isBalanced(node->left, leftHeight)
					&& abs(leftHeight - height) <= 1) {
						height += (leftHeight > height ? 2 : 1);
						return true;
				}
				return false;
			};

			void printOn(std::ostream &o) const;

	};//class TreeBase

//Obj Func
template <class T> struct TestOrd {
	bool &is_order;
	const T *previous;
	TestOrd(const T &p, bool &o) : is_order(o), previous(&p) {}
	void operator() (const T &e) {
		if (e < *previous) is_order = false;
		else previous = &e;
	}
};

template<class T, class A>
bool TreeBase<T,A>::isOrded() const {
	if (size() < 2) return true;
	bool is_order = true;
	TreeBase::inorder(TestOrd<T>(dummy->left->value, is_order));
	return is_order;
}

template <class T> class PrintOn { // Objecto funcao
	int nivel;
	std::ostream &o;
public:
	PrintOn(std::ostream &out) : nivel(0), o(out) {}
	PrintOn(const PrintOn &p) : nivel(p.nivel+1), o(p.o) {}
	void operator()(const T &data) {
		for (int i= 0; i < nivel; ++ i) o << "   ";
		o << data << std::endl;
	}
};

template<class T, class A>
void TreeBase<T,A>::printOn(std::ostream &o) const
	{ inorder( PrintOn<T>(o) ); }


#undef CONTAINER
};//namespace ft


#endif