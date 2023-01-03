#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "Node.hpp"
#include "iterator_traits.hpp"

namespace ft {
#define TRAITS ft::iterator_traits<T>
	template<typename T, typename Pointer, typename Reference>
	class bidirectional_iterator :
	public ft::iterator<ft::bidirectional_iterator_tag, T>, public TRAITS {
		public:
			IMPORT_TRAIT(iterator_category);
			IMPORT_TRAIT(value_type);
			IMPORT_TRAIT(pointer);
			IMPORT_TRAIT(reference);
			IMPORT_TRAIT(difference_type);
			typedef bidirectional_iterator<T, pointer, reference>	iterator;
			typedef bidirectional_iterator<T, pointer, reference>	const_iterator;
			typedef Node<value_type>								node;
			typedef node*											iterator_type;

		private:
			iterator_type	_ptr;

		public:
			bidirectional_iterator() : _ptr(NULL) {};

			bidirectional_iterator(iterator_type ptr) : _ptr(ptr) {};

			bidirectional_iterator(const bidirectional_iterator &other) { *this = other; };

			bidirectional_iterator &operator=(const bidirectional_iterator &other) {
				if (this != &other)
					_ptr = other._ptr;
				return *this;
			};

			~bidirectional_iterator() {};

			operator const_iterator() const { return const_iterator(_ptr); };

			bool operator==(const iterator &other) const { return _ptr == other._ptr; };

			bool operator!=(const iterator &other) const { return _ptr != other._ptr; };

			reference operator*() { return _ptr->data; };

			pointer operator->() { return &_ptr->data; };

			iterator &operator++() {
				_ptr = _ptr->next();
				return *this;
			};

			iterator operator++(int) {
				iterator tmp = *this;
				_ptr = _ptr->next();
				return tmp;
			};

			iterator &operator--() {
				_ptr = _ptr->prev();
				return *this;
			};

			iterator operator--(int) {
				iterator tmp = *this;
				_ptr = _ptr->prev();
				return tmp;
			};

	};//class bidirectional_iterator
	#undef TRAITS
};//namespace ft

#endif