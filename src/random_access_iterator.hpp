#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template <typename T> class random_access_iterator :
		public ft::iterator<ft::random_access_iterator_tag, T>
	{

		typedef typename ft::iterator_traits<T> traits;

		public:

			typedef	T									iterator_type;
			typedef typename traits::iterator_category	iterator_category;
			typedef typename traits::value_type			value_type;
			typedef typename traits::pointer			pointer;
			typedef typename traits::reference			reference;
			typedef typename traits::difference_type	difference_type;

		private:
			iterator_type _ptr;

		public:

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

			random_access_iterator(): _ptr(NULL) {};

			explicit random_access_iterator(pointer ptr): _ptr(ptr) {};

			random_access_iterator(const random_access_iterator& instance) {*this = instance;};

			~random_access_iterator() {};

			random_access_iterator& operator=(const random_access_iterator& rhs) {
				this->_ptr = rhs.base();
				return *this;
			};

/******************************************************************************/
/*								Base									      */
/******************************************************************************/

			iterator_type base(void) const { return (this->_ptr); };

/******************************************************************************/
/*								Operators								      */
/******************************************************************************/

			bool operator==(random_access_iterator& rhs) {
				return this->_ptr == rhs._ptr;
			};

			bool operator!=(random_access_iterator& rhs) {
				return this->_ptr != rhs._ptr;
			};

			bool operator>(random_access_iterator& rhs) {
				return this->_ptr > rhs._ptr;
			};

			bool operator>=(random_access_iterator& rhs) {
				return this->_ptr >= rhs._ptr;
			};

			bool operator<(random_access_iterator& rhs) {
				return this->_ptr < rhs._ptr;
			};

			bool operator<=(random_access_iterator& rhs) {
				return this->_ptr <= rhs._ptr;
			};

			random_access_iterator& operator++(void) {
				this->_ptr++;
				return (*this);
			};

			random_access_iterator& operator--(void) {
				this->_ptr--;
				return (*this);
			};

			random_access_iterator operator++(int) {
				random_access_iterator copy = *this;
				this->_ptr++;
				return (copy);
			};

			random_access_iterator operator--(int) {
				random_access_iterator copy = *this;
				this->_ptr--;
				return (copy);
			};

			random_access_iterator operator+(int rhs) {
				return (random_access_iterator(this->_ptr + rhs));
			};

			random_access_iterator operator-(int rhs) {
				return (random_access_iterator(this->_ptr - rhs));
			};

			random_access_iterator& operator+=(int rhs) {
				this->_ptr += rhs;
				return (*this);
			};

			random_access_iterator& operator-=(int rhs) {
				this->_ptr -= rhs;
				return (*this);
			};

			int operator+(random_access_iterator& rhs) {
				return (this->_ptr + rhs._ptr);
			};

			int operator-(random_access_iterator& rhs) {
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