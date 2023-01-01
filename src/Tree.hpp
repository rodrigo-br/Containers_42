#ifndef TREE_H
#define TREE_H

#include "TreeBase.hpp"
#include <string>
#include <locale>
#include <algorithm>

namespace ft {

	struct CompStr {
		bool operator() (std::string a, std::string b) {
			return std::transform(a.begin(), a.end(), a.begin(), ::toupper) <
			std::transform(b.begin(), b.end(), b.begin(), ::toupper);
		}
	};

	template<class T> struct less {
		bool operator() (const T& x, const T& y) const { return x < y; }
	};

	template<class K, class V = K> struct Identity {
		const K &operator() (const V &v) const { return v; }
	};

#define CONTAINER TreeBase<Value, Alloc>
/**
 * @brief Para fazer cumprir requisitos impostos pelo standard ANSI/ISO C++,
 * a classe Tree deriva da versão TreeBase, que implementa a estrutura de dados
 * ABP (Árvore Binária de Pesquisa)
 *  
 * @param Key  tipo da chave de pesquisa
 * @param Value  tipo do valor armazenado nos nós
 * @param KeyFromValue  infere Key a partir de Value
 * @param Compare  estabelece critério de ordenação das chaves
 * @param Alloc  tipo de alocação de memória
*/
template <class Key, class Value,
		class KeyFromValue = Identity<Key, Value>,
		class Compare = less<Key>,
		class Alloc = std::allocator<Value> >
		class Tree : public CONTAINER {
			public:
				IMPORT_TYPE(iterator);
				IMPORT_TYPE(const_iterator);
				IMPORT_TYPE(size_type);
				typedef Key				key_type;
				typedef Compare			key_compare;
				typedef Value			value_type;
				typedef typename TreeBase<value_type
				>::NodePtr 				NodePtr;
				typedef typename TreeBase<value_type
				>::ConstNodePtr 		ConstNodePtr;

			protected:
				typedef KeyFromValue	kfromv_type;
				key_compare				cmp;
				KeyFromValue			kFromV;

				KeyFromValue key_extract() const { return kFromV; };

				const Key &key(const Value &v) const { return kFromV(v); };

				template <bool MULTI>
				pair<iterator, bool> insertNode(const value_type &v) {
					NodePtr node;
					if (CONTAINER::root == NULL)
						node = CONTAINER::root = CONTAINER::dummy->left = CONTAINER::dummy->right = CONTAINER::newNode(CONTAINER::dummy, v);
					else {
						node = CONTAINER::root;
						for (;;) {
							if (cmp(key(v), key(node->value))) {
								if (node->left != NULL)
									node = node->left;
								else {
									node = CONTAINER::insertLeft(node, v);
									break ;
								}
							} else if (MULTI || cmp(key(node->value), key(v))) {
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

			public:
				Tree(const key_compare &c = key_compare(), const Alloc &a = Alloc(),
				const kfromv_type &kv = kfromv_type()) : CONTAINER(a), cmp(c), kFromV(kv) {};

				key_compare key_comp() const { return cmp; };

				iterator find(const key_type& k) {
					NodePtr node = CONTAINER::root;
					NodePtr aux = CONTAINER::dummy;
					while (node != NULL) {
						if (cmp(key(node->value), k))
							node = node->right;
						else {
							aux = node;
							node = node->left;
						}
					}
					return (aux == CONTAINER::dummy || cmp(k, key(aux->value)))
					? CONTAINER::end() : getIterator(aux);
				};

				pair<iterator, bool> insertUni(const value_type &v) {
					return insertNode<false>(v);
				};

				iterator insertMulti(const value_type &v) {
					return insertNode<true>(v).first;
				};

				void erase(iterator it) { CONTAINER::erase(it); };

				size_type erase(const key_type &k) {
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


		};//class Tree
		#undef CONTAINER

};//namespace ft

#endif