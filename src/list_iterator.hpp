#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "iterator_traits.hpp"

namespace ft {
	template <typename T> class list_iterator
	{
		public:

			typedef	list_iterator<T>					iterator;
			typedef list_iterator<const T>				const_iterator;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::ptrdiff_t						difference_type;
			
		private:

			pointer	_ptr;

		public:

			list_iterator() : _ptr(NULL) {};

			explicit list_iterator(pointer ptr) : _ptr(ptr) {};

			list_iterator(const iterator& instance) { *this = instance; };

			~list_iterator() {};

			iterator& operator=(const iterator& rhs) {
				_ptr = rhs._ptr;
				return *this;
			};

			pointer base(void) const { return (_ptr); };

			reference operator*(void) const { return *_ptr; };

			pointer operator->(void) const { return _ptr; };

			iterator& operator++(void) {
				_ptr = _ptr->next;
				return *this;
			};

			iterator operator++(int) {
				iterator tmp(*this);
				++*this;
				return tmp;
			};

			iterator& operator--(void) {
				_ptr = _ptr->prev;
				return *this;
			};

			iterator operator--(int) {
				iterator tmp(*this);
				--*this;
				return tmp;
			};
			
			bool operator==(const iterator& rhs) { return _ptr == rhs._ptr; };

			bool operator!=(const iterator& rhs) { return _ptr != rhs._ptr; };


	}; // class list_iterator

}; // namespace ft

#endif