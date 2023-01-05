#ifndef BIDIRECTIONAL_iterator_H
#define BIDIRECTIONAL_iterator_H

#include "Node.hpp"
#include "iterator_traits.hpp"

namespace ft {
#define TRAITS ft::bidirectional_iterator<ft::bidirectional_iterator_tag, T>
	template<typename T, class Compare>
	class bidirectional_iterator : public TRAITS {
		public:
			IMPORT_TRAIT(value_type);
			IMPORT_TRAIT(iterator_category);
			IMPORT_TRAIT(pointer);
			IMPORT_TRAIT(reference);
			IMPORT_TRAIT(difference_type);

			T 		*_node;
			T 		*_tail;
			Compare _comp;


		public:
			bidirectional_iterator(const Compare &comp = Compare()) :
				_node(NULL), _tail(NULL), _comp(comp) {};

			bidirectional_iterator(T *node, T *tail, const Compare &comp = Compare()) :
				_node(node), _tail(tail), _comp(comp) {};

			bidirectional_iterator(const bidirectional_iterator &other) { *this = other; };

			bidirectional_iterator &operator=(const bidirectional_iterator &other) {
				if (this != &other)
					_node = other._node;
					_tail = other._tail;
					_comp = other._comp;
				return *this;
			};

			virtual ~bidirectional_iterator() {};

			

			bool operator==(const bidirectional_iterator &other) const { return _node == other._node; };

			bool operator!=(const bidirectional_iterator &other) const { return _node != other._node; };

			reference operator*() { return _node->data; };

			pointer operator->() { return &_node->data; };

			bidirectional_iterator &operator++() {
				T *tmp = _node;

				if (_node->next() == _tail) {
					tmp = _node->parent;
					while (tmp != _tail && _comp(tmp->value.first, _node->value.first))
						tmp = tmp->parent;
					_node = tmp;
				} else if (tmp == _tail)
					_node = _tail->right;
				else {
					tmp = _node->right;
					if (tmp == _tail->parent && tmp->right == _tail)
						_node = tmp;
					else {
						while (tmp->left != _tail)
							tmp = tmp->left;
					}
					_node = tmp;
				}
				return *this;
			};

			bidirectional_iterator operator++(int) {
				bidirectional_iterator tmp = *this;
				operator++();
				return tmp;
			};

			bidirectional_iterator &operator--() {
				T *tmp = _node;

				if (_node->left == _tail) {
					tmp = _node->parent;
					while (tmp != _tail && _comp(_node->value.first, tmp->value.first))
						tmp = tmp->parent;
					_node = tmp;
				} else if (tmp == _tail)
					_node = _tail->right;
				else {
					tmp = _node->left;
					if (tmp == _tail->parent && tmp->left == _tail)
						_node = tmp;
					else {
						while (tmp->right != _tail)
							tmp = tmp->right;
					}
					_node = tmp;
				}
				return *this;
			};

			bidirectional_iterator operator--(int) {
				bidirectional_iterator tmp = *this;
				operator--();
				return tmp;
			};

	};//class bidirectional_iterator
	#undef TRAITS

	#define TRAITS ft::const_bidirectional_iterator<ft::bidirectional_iterator_tag, T>
	template<typename T, class Compare>
	class const_bidirectional_iterator : public TRAITS {
		public:
			IMPORT_TRAIT(value_type);
			IMPORT_TRAIT(iterator_category);
			IMPORT_TRAIT(pointer);
			IMPORT_TRAIT(reference);
			IMPORT_TRAIT(difference_type);

			T 		*_node;
			T 		*_tail;
			Compare _comp;


		public:
			const_bidirectional_iterator(const Compare &comp = Compare()) :
				_node(NULL), _tail(NULL), _comp(comp) {};

			const_bidirectional_iterator(T *node, T *tail, const Compare &comp = Compare()) :
				_node(node), _tail(tail), _comp(comp) {};

			const_bidirectional_iterator(const const_bidirectional_iterator &other) { *this = other; };

			const_bidirectional_iterator &operator=(const const_bidirectional_iterator &other) {
				if (this != &other)
					_node = other._node;
					_tail = other._tail;
					_comp = other._comp;
				return *this;
			};

			virtual ~const_bidirectional_iterator() {};

			

			bool operator==(const const_bidirectional_iterator &other) const { return _node == other._node; };

			bool operator!=(const const_bidirectional_iterator &other) const { return _node != other._node; };

			reference operator*() { return _node->data; };

			pointer operator->() { return &_node->data; };

			const_bidirectional_iterator &operator++() {
				T *tmp = _node;

				if (_node->next() == _tail) {
					tmp = _node->parent;
					while (tmp != _tail && _comp(tmp->value.first, _node->value.first))
						tmp = tmp->parent;
					_node = tmp;
				} else if (tmp == _tail)
					_node = _tail->right;
				else {
					tmp = _node->right;
					if (tmp == _tail->parent && tmp->right == _tail)
						_node = tmp;
					else {
						while (tmp->left != _tail)
							tmp = tmp->left;
					}
					_node = tmp;
				}
				return *this;
			};

			const_bidirectional_iterator operator++(int) {
				const_bidirectional_iterator tmp = *this;
				operator++();
				return tmp;
			};

			const_bidirectional_iterator &operator--() {
				T *tmp = _node;

				if (_node->left == _tail) {
					tmp = _node->parent;
					while (tmp != _tail && _comp(_node->value.first, tmp->value.first))
						tmp = tmp->parent;
					_node = tmp;
				} else if (tmp == _tail)
					_node = _tail->right;
				else {
					tmp = _node->left;
					if (tmp == _tail->parent && tmp->left == _tail)
						_node = tmp;
					else {
						while (tmp->right != _tail)
							tmp = tmp->right;
					}
					_node = tmp;
				}
				return *this;
			};

			const_bidirectional_iterator operator--(int) {
				const_bidirectional_iterator tmp = *this;
				operator--();
				return tmp;
			};

	};//class const_bidirectional_iterator
	#undef TRAITS
};//namespace ft

#endif