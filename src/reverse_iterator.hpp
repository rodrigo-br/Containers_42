#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "iterator_traits.hpp"

namespace ft{
template <typename T> class reverse_iterator : public std::iterator 
						< typename ft::iterator_traits<T>::iterator_category,
						typename ft::iterator_traits<T>::value_type,
						typename ft::iterator_traits<T>::difference_type,
						typename ft::iterator_traits<T>::pointer,
						typename ft::iterator_traits<T>::reference > {
	public:

		typedef T													iterator_type;
		typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<T>::value_type			value_type;
		typedef typename ft::iterator_traits<T>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T>::pointer			pointer;
		typedef typename ft::iterator_traits<T>::reference			reference;

	private:

		iterator_type	_current;

	public:	

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

		reverse_iterator() : _current(NULL) {};

		explicit reverse_iterator (iterator_type it) : _current(it) {};

		reverse_iterator (const reverse_iterator& rev_it) : _current(rev_it.base()) {};

		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {};

		~reverse_iterator() {};

/******************************************************************************/
/*					Operators											      */
/******************************************************************************/

		template <class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other) {
			return *this;
		};

/******************************************************************************/
/*					Base												      */
/******************************************************************************/

		iterator_type base(void) const { return _current; };
	};
};

#endif