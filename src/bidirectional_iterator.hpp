#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "iterator_traits.hpp"
#include "TreeBase.hpp"
#include "utility.hpp"

namespace ft {
#define TRAITS ft::iterator_traits<T>
	template <typename T, typename Pointer> class bidirectional_iterator :
		public ft::iterator<ft::bidirectional_iterator_tag, T>, public TRAITS
	{

		public:
			IMPORT_TRAIT(iterator_category);
			IMPORT_TRAIT(value_type);
			IMPORT_TRAIT(pointer);
			IMPORT_TRAIT(reference);
			IMPORT_TRAIT(difference_type);
			typedef	T		iterator_type;

		private:
			iterator_type	_ptr;
			Pointer			_t_ptr;

		public:

/******************************************************************************/
/*					Constructors/Destructors							      */
/******************************************************************************/

			bidirectional_iterator(): _ptr(NULL) {};

			explicit bidirectional_iterator(pointer ptr): _ptr(ptr) {};

			bidirectional_iterator(const bidirectional_iterator& instance) { *this = instance; };

			~bidirectional_iterator() {};

			bidirectional_iterator& operator=(const bidirectional_iterator& rhs) {
				_ptr = rhs.base();
				return *this;
			};

/******************************************************************************/
/*								Base									      */
/******************************************************************************/

			iterator_type base(void) const { return (_ptr); };

/******************************************************************************/
/*							Operators									      */
/******************************************************************************/

			void increment() {
				if (_t_ptr->right == NULL) {
					Pointer ptr = _t_ptr;
					while ((_t_ptr = _t_ptr->parent)->right == ptr) {
						ptr = _t_ptr;
					}
				} else {
					_t_ptr = leftMost(_t_ptr->right);
				}
			};

			Pointer leftMost() {
				while (_t_ptr->left != NULL) {
					_t_ptr = _t_ptr->left;
				}
				return _t_ptr;
			};

			void decrement() {
				if (_t_ptr->left == NULL) {
					Pointer ptr = _t_ptr;
					while ((_t_ptr = _t_ptr->parent)->left == ptr) {
						ptr = _t_ptr;
					}
				} else {
					if (_t_ptr->parent == _t_ptr)
						_t_ptr = _t_ptr->right;
					else
						_t_ptr = rightMost(_t_ptr->left);
				}
			};

			Pointer rightMost() {
				while (_t_ptr->right != NULL) {
					_t_ptr = _t_ptr->right;
				}
				return _t_ptr;
			};

			bidirectional_iterator &operator++() {
				increment();
				return *this;
			};

			bidirectional_iterator operator++(int) {
				bidirectional_iterator copy = *this;
				increment();
				return copy;
			};

			bidirectional_iterator &operator--() {
				decrement();
				return *this;
			};

			bidirectional_iterator operator--(int) {
				bidirectional_iterator copy = *this;
				decrement();
				return copy;
			};

			reference operator*() const { return (*_ptr); };

			pointer operator->() const { return (_ptr); };

			bool operator==(bidirectional_iterator& rhs) {
				return _ptr == rhs._ptr;
			};

			bool operator!=(bidirectional_iterator& rhs) {
				return _ptr != rhs._ptr;
			};

			bool operator>(bidirectional_iterator& rhs) {
				return _ptr > rhs._ptr;
			};

			bool operator<(bidirectional_iterator& rhs) {
				return _ptr < rhs._ptr;
			};

			bool operator>=(bidirectional_iterator& rhs) {
				return _ptr >= rhs._ptr;
			};

			bool operator<=(bidirectional_iterator& rhs) {
				return _ptr <= rhs._ptr;
			};


	};//class bidirectional_iterator
#undef TRAITS
};//namespace ft

#endif