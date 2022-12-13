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
/*					Operators							      */
/******************************************************************************/

			random_access_iterator &operator=(const random_access_iterator &rhs) {
				_ptr = rhs._ptr;
				return *this;
			}

			bool operator==(const random_access_iterator &rhs) const {
				return _ptr == rhs.base();
			}

			bool operator!=(const random_access_iterator &rhs) const {
				return _ptr != rhs.base();
			}

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

			/*

For mutable iterators (non-constant iterators):
Can be dereferenced as an lvalue (if in a dereferenceable state).	*a = t
Can be incremented (if in a dereferenceable state).
The result is either also dereferenceable or a past-the-end iterator.
Two iterators that compare equal, keep comparing equal after being both increased.
++a
a++
*a++
Can be decremented (if a dereferenceable iterator value precedes it).
--a
a--
*a--
Supports the arithmetic operators + and - between an iterator and an integer value,
 or subtracting an iterator from another.	a + n
n + a
a - n
a - b
Can be compared with inequality relational operators (<, >, <= and >=).	a < b
a > b
a <= b
a >= b
Supports compound assignment operations += and -=	a += n
a -= n
Supports the offset dereference operator ([])	a[n]

Where X is a random-access iterator type, a and b are objects of this iterator type,
 n is a value of its difference type, and t is an object of the type pointed by
  the iterator type (or some other type that can be assigned to the lvalue
   returned by dereferencing an object of type X).*/

	};
};

#endif