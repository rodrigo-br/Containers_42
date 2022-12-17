#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

namespace ft {
	template <typename Category,
			typename T,
			typename Distance = std::ptrdiff_t,
			typename Pointer = T*,
			typename Reference = T&>
	struct iterator {
		typedef Category								iterator_category;
		typedef T										value_type;
		typedef Distance								difference_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
	};

	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category 	iterator_category;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag 		iterator_category;
		typedef T 										value_type;
		typedef std::ptrdiff_t 							difference_type;
		typedef T* 										pointer;
		typedef T& 										reference;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef std::random_access_iterator_tag 		iterator_category;
		typedef T 										value_type;
		typedef std::ptrdiff_t 							difference_type;
		typedef const T* 								pointer;
		typedef const T& 								reference;
	};

};//namespace ft 

#endif