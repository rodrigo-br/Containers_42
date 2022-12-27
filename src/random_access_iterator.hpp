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

		private:
			pointer	_ptr;

		public:

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

			random_access_iterator(): _ptr(NULL) {};

			explicit random_access_iterator(pointer ptr): _ptr(ptr) {};

			random_access_iterator(const random_access_iterator& instance) {*this = instance;};

			~random_access_iterator() {};

			random_access_iterator& operator=(const random_access_iterator& rhs) {
				this->_ptr = rhs._ptr;
				return *this;
			};

/******************************************************************************/
/*								Base									      */
/******************************************************************************/

			pointer base(void) const { return (this->_ptr); };

/******************************************************************************/
/*								Operators								      */
/******************************************************************************/

			operator const_iterator() const { return const_iterator(_ptr); };

			bool operator==(const iterator& rhs) {
				return this->_ptr == rhs._ptr;
			};

			bool operator!=(const iterator& rhs) {
				return this->_ptr != rhs._ptr;
			};

			bool operator>(const iterator& rhs) {
				return this->_ptr > rhs._ptr;
			};

			bool operator>=(const iterator& rhs) {
				return this->_ptr >= rhs._ptr;
			};

			bool operator<(const iterator& rhs) {
				return this->_ptr < rhs._ptr;
			};

			bool operator<=(const iterator& rhs) {
				return this->_ptr <= rhs._ptr;
			};

			iterator& operator++(void) {
				this->_ptr++;
				return (*this);
			};

			iterator& operator--(void) {
				this->_ptr--;
				return (*this);
			};

			iterator operator++(int) {
				iterator copy(*this);
				this->_ptr++;
				return (copy);
			};

			iterator operator--(int) {
				iterator copy(*this);
				this->_ptr--;
				return (copy);
			};

			iterator operator+(int rhs) {
				return (iterator(this->_ptr + rhs));
			};

			iterator operator-(int rhs) {
				return (iterator(this->_ptr - rhs));
			};

			iterator& operator+=(int rhs) {
				this->_ptr += rhs;
				return (*this);
			};

			iterator& operator-=(int rhs) {
				this->_ptr -= rhs;
				return (*this);
			};

			int operator+(const iterator& rhs) {
				return (this->_ptr + rhs._ptr);
			};

			int operator-(const iterator& rhs) {
				return (this->_ptr - rhs._ptr);
			};

			reference	operator[](const int n) const {
				return (this->_ptr[n]);
			};

			reference	operator*(void) const {
				return *(this->_ptr);
			};

			pointer		operator->(void) {
				return (this->_ptr);
			};
	};

/******************************************************************************/
/*						Non-member Operators							      */
/******************************************************************************/

	template<class T>
	bool operator==(const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs) {
		return lhs.base() == rhs.base();
	};

	template<class T>
	bool operator!=(const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs) {
		return lhs.base() != rhs.base();
	};

	template<class T>
	bool operator<(const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs) {
		return lhs.base() < rhs.base();
	};

	template<class T>
	bool operator<=(const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs) {
		return lhs.base() <= rhs.base();
	};

	template<class T>
	bool operator>(const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs) {
		return lhs.base() > rhs.base();
	};

	template<class T>
	bool operator>=(const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs) {
		return lhs.base() >= rhs.base();
	};

	template<class T_L, class T_R>
	bool operator==(const ft::random_access_iterator<T_R>& lhs,
					const ft::random_access_iterator<T_L>& rhs) {
		return lhs.base() == rhs.base();
	};

	template<class T_L, class T_R>
	bool operator!=(const ft::random_access_iterator<T_L>& lhs,
					const ft::random_access_iterator<T_R>& rhs) {
		return lhs.base() != rhs.base();
	};

	template<class T_L, class T_R>
	bool operator<(const ft::random_access_iterator<T_L>& lhs,
					const ft::random_access_iterator<T_R>& rhs) {
		return lhs.base() < rhs.base();
	};

	template<class T_L, class T_R>
	bool operator<=(const ft::random_access_iterator<T_L>& lhs,
					const ft::random_access_iterator<T_R>& rhs) {
		return lhs.base() <= rhs.base();
	};

	template<class T_L, class T_R>
	bool operator>(const ft::random_access_iterator<T_L>& lhs,
					const ft::random_access_iterator<T_R>& rhs) {
		return lhs.base() > rhs.base();
	};

	template<class T_L, class T_R>
	bool operator>=(const ft::random_access_iterator<T_L>& lhs,
					const ft::random_access_iterator<T_R>& rhs) {
		return lhs.base() >= rhs.base();
	};
};//namespace ft

#endif