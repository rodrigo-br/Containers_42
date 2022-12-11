#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

namespace ft {
	template <class Iterator> class iterator_traits {
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};
	
	template <class T> class iterator_traits<T*> {
		typedef typename std::ptrdiff_t						difference_type;
		typedef typename T									value_type;
		typedef typename T*									pointer;
		typedef typename IT&								reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class T> class iterator_traits<const T*> {
		typedef typename std::ptrdiff_t						difference_type;
		typedef typename T									value_type;
		typedef typename T const*							pointer;
		typedef typename IT const&							reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};
}

#endif