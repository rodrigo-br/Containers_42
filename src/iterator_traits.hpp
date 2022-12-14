#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

namespace ft {
	template <class Iterator> class iterator_traits {
		public:
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};
	
	template <typename T> class iterator_traits<T*> {
		public:
		typedef typename std::ptrdiff_t						difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class T> class iterator_traits<const T*> {
		public:
		typedef typename std::ptrdiff_t						difference_type;
		typedef T											value_type;
		typedef T const*									pointer;
		typedef T const&									reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};
}

#endif