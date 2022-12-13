#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template <typename T> class random_access_iterator
	{
		public:

			typedef	random_access_iterator<T>			iterator;
			typedef random_access_iterator<const T>		const_iterator;
			typedef std::random_access_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::ptrdiff_t						difference_type;
			
		protected:

			pointer _ptr;
		
		public:

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

			random_access_iterator() : _ptr(NULL) {};

			explicit random_access_iterator(pointer ptr) : _ptr(ptr) {};

			random_access_iterator(const random_access_iterator &rai) { *this = rai; };

			template<T>
			random_access_iterator(const iterator &ptr) : _ptr(ptr.base()) {};

			~random_access_iterator() {};


			pointer base(void) const { return _ptr; };

/******************************************************************************/
/*					Operators							     				  */
/******************************************************************************/

			random_access_iterator &operator=(const random_access_iterator &rhs) {
				_ptr = rhs._ptr;
				return *this;
			};

			bool operator==(const random_access_iterator &rhs) const {
				return _ptr == rhs.base();
			};

			bool operator!=(const random_access_iterator &rhs) const {
				return _ptr != rhs.base();
			};

			reference operator*(void) const { return *_ptr; };

			pointer	operator->() const { return _ptr; };

			random_access_iterator &operator++() {
				++_ptr;
				return *this;
			};

			random_access_iterator &operator++(int) {
				random_access_iterator tmp = *this;
				++_ptr;
				return *tmp;
			};

			random_access_iterator &operator--() {
				--_ptr;
				return *this;
			};

			random_access_iterator &operator--(int) {
				random_access_iterator tmp = *this;
				--_ptr;
				return *tmp;
			};
			
			random_access_iterator operator+(difference_type n) const {
				return random_access_iterator(_ptr + n);
			};

			random_access_iterator operator-(difference_type n) const {
				return random_access_iterator(_ptr - n);
			};

			random_access_iterator &operator+=(difference_type n) {
				_ptr += n;
				return *this;
			};

			random_access_iterator &operator-=(difference_type n) {
				_ptr -= n;
				return *this;
			};

			bool operator<(const random_access_iterator &rhs) const {
				return _ptr < rhs.base();
			};

			bool operator<=(const random_access_iterator &rhs) const {
				return _ptr <= rhs.base();
			};

			bool operator>(const random_access_iterator &rhs) const {
				return _ptr > rhs.base();
			};

			bool operator>=(const random_access_iterator &rhs) const {
				return _ptr >= rhs.base();
			};

			reference operator[](difference_type n) const {
				return _ptr[n];
			};

			iterator operator+(int rhs) {
				return (iterator(_ptr + rhs));
			}

			iterator operator-(int rhs) {
				return (iterator(_ptr - rhs));
			}

			int operator+(const iterator& rhs) {
				return (_ptr + rhs._ptr);
			}

			int operator-(const iterator& rhs) {
				return (_ptr - rhs._ptr);
			}

			template<typename It>
			operator random_access_iterator<It>() const {
				return random_access_iterator<It>(_ptr);
			};

	};
};

#endif