#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "iterator_traits.hpp"

template <class T> class reverse_iterator {
	typedef typename T											iterator_type;
	typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<T>::value_type			value_type;
	typedef typename ft::iterator_traits<T>::difference_type	difference_type;
	typedef typename ft::iterator_traits<T>::pointer			pointer;
	typedef typename ft::iterator_traits<T>::reference			reference;
};

#endif