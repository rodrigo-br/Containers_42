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

namespace ft {
#define CONTAINER ft::Container<T, Alloc>
	template<class T, class Alloc = std::allocator<T> >
	class TreeBase : public CONTAINER {

		public:
			IMPORT_TYPE(allocator_type);
			IMPORT_TYPE(reference);
			IMPORT_TYPE(const_reference);
			IMPORT_TYPE(pointer);
			IMPORT_TYPE(const_pointer);
			IMPORT_TYPE(size_type);
			IMPORT_TYPE(difference_type);
		
		protected:
			struct													Node;
			typedef typename Alloc::template rebind<Node>::other	ANode;
			typedef typename ANode::pointer							NodePtr;
			typedef typename ANode::const_pointer					ConstNodePtr;
			struct Node {
				T			value;
				NodePtr		parent;
				NodePtr		left;
				NodePtr		right;
			};
			ANode		alloc;
			size_type	_size;
			NodePtr		root;
			NodePtr		dummy;
			typedef ft::bidirectional_iterator<pointer, NodePtr>		iterator;
			typedef ft::bidirectional_iterator<const_pointer, NodePtr>	const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		public:

			NodePtr newNode() {
				NodePtr node = alloc.allocate(1);
				return node->left = node->right = node->parent = node;
			};

			NodePtr newNode(NodePtr parent, const T &value) {};

			NodePtr newNode(ConstNodePtr parent) {};

			void deleteNode(NodePtr node) {};

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

			template<bool MULTI> pair<iterator, bool> insertNode(const T &value) {
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

			NodePtr insertLeft(NodePtr node, const T &value) {
				node->left = newNode(node, value);
				if (node == dummy->left)
					dummy->left = node->left;
				return node->left;
			};

			NodePtr insertRight(NodePtr node, const T &value) {
				node->right = newNode(node, value);
				if (node == dummy->right)
					dummy->right = node->right;
				return node->right;
			};

			// static void setParent(NodePtr child, NodePtr father) {};

			// void transferParent(NodePtr x, NodePtr y) {};

			// void transferNode(NodePtr x, NodePtr y) {};

			// void clear(NodePtr node) {};

			// NodePtr copy(ConstNodePtr node) {};

			// void copy(const TreeBase &x) {};

			// static bool isBalanced(ConstNodePtr node, int &height) {};

			// static void treeToList(NodePtr node, NodePtr &head) {};

			// static NodePtr listToTree(NodePtr &head, size_type size) {};

			iterator getIterator(NodePtr node) { return iterator(node); };

			NodePtr getNode(iterator i) { return i.base(); };

			TreeBase(const allocator_type &a = allocator_type()) :
				alloc(a), _size(0), root(NULL), dummy(newNode()) {};
			
			TreeBase(const TreeBase &x) {};

			~TreeBase() {};

			TreeBase &operator=(const TreeBase &x) {};

			allocator_type get_allocator() const { return alloc; };

			template<class Visit> void preorder(Visit visit) const { preorder(root, visit); };

			template<class Visit> void inorder(Visit visit) const { inorder(root, visit); };

			template<class Visit> void postorder(Visit visit) const { postorder(root, visit); };

			iterator begin() { return iterator(dummy->left); };

			iterator end() { return iterator(dummy); };

			const_iterator begin() const { return const_iterator(dummy->left); };

			const_iterator end() const { return const_iterator(dummy); };

			size_type size() const { return _size; };

			bool empty() const { return size() == 0; };

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

			pair<iterator, bool> insertUni(const T &value) {
				return insertNode<false>(value);
			};

			iterator insertMulti(const T &value) {
				return insertNode<true>(value).first;
			};

			// size_type erase(const T &value) {};

			// void erase(iterator i) {};

			// void clear() {};

			// void balance() {};

			void display() const {
				inorder(displayValue<T>());
			};

			// bool isOrded() const {};

			// bool isBalanced() const {};

			// void printOn(std::ostream &os) const {};

			template<class Tr>
			void displayValue(const Tr &value) {
				std::cout << value << " ";
			};


	};//class TreeBase

};//namespace ft


#endif