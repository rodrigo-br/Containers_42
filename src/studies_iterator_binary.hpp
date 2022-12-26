#ifndef STUDIES_ITERATOR_BINARY_H
#define STUDIES_ITERATOR_BINARY_H

#include "studies_binary_tree.hpp"
#include "iterator_traits.hpp"
 
template<class T, class Alloc = std::allocator<T> >class TreeBase;

namespace ft {
	template <typename T> class tree_iterator {

	public:
		typedef tree_iterator<T>						iterator;
		typedef tree_iterator<const T>					const_iterator;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef std::ptrdiff_t							difference_type;

	protected:
		pointer current;

		void inc() {
			if (current->right == NULL) {
				pointer ptr = current;
				while ((current = current->parent)->right == ptr) {
					ptr = current;
				}
			}
			else
				current = TreeBase<T>::leftMost(current->right);
		};

		void dec() {
			if (current->left == NULL) {
				pointer ptr = current;
				while ((current = current->parent)->left == ptr) {
					ptr = current;
				}
			}
			else {
				if (current->parent  == current)
					current = current->right;
				else
					current = TreeBase<T>::rightMost(current->left);
			}
		};
		

	public:
		tree_iterator() {};

		tree_iterator(pointer node) : current(node) {};

		tree_iterator(const iterator &it) : current(it.current) {};

		iterator& operator++() {
			inc();
			return *this;
		};

		iterator operator++(int) {
			iterator tmp(*this);
			inc();
			return tmp;
		};

		iterator& operator--() {
			dec();
			return *this;
		};

		iterator operator--(int) {
			iterator tmp(*this);
			dec();
			return tmp;
		};

		reference operator*() const {
			return current->value;
		};

		pointer operator->() const {
			return &(current->value);
		};

		bool operator==(iterator it) const {
			return current == it.current;
		};

		bool operator!=(iterator it) const {
			return !(*this == it);
		};

	}; // iterator

}; // namespace ft	

#endif