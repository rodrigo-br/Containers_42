#ifndef MAP_H
#define MAP_H

//life is sucks

#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include <memory>

namespace ft {

template<class Key, class T,
class Compare = std::less<Key>,
class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

	public:
		typedef Key 													key_type;
		typedef T 														mapped_type;
		typedef ft::pair<const Key, T> 									value_type;
		typedef Compare 												key_compare;
		typedef Alloc 													allocator_type;
		typedef std::ptrdiff_t 											difference_type;
		typedef size_t 													size_type;
		typedef Node<value_type> 										map_node;
		typedef typename Alloc::template rebind<map_node>::other 		alloc_node;
		typedef typename Alloc::reference 								reference;
		typedef typename Alloc::const_reference 						const_reference;
		typedef typename Alloc::pointer 								pointer;
		typedef typename Alloc::const_pointer 							const_pointer;
		typedef ft::bidirectional_iterator<
		value_type, pointer, reference> 								iterator;
		typedef ft::bidirectional_iterator<
		value_type, const_pointer, const_reference> 					const_iterator;
		typedef reverse_iterator<iterator> 								reverse_iterator;
		typedef reverse_iterator<const_iterator> 						const_reverse_iterator;

}; //class map

}; //namespace ft

#endif