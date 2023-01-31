#ifndef MAP_HPP
# define MAP_HPP

#include "rbtree.hpp"

namespace ft {

template <class K, class T, class Compare = less<K>, class Alloc = std::allocator<ft::pair<K, T> > >
class map : public ft::RBTree<K, ft::pair<K, T>, ft::FirstOfPair<K, T>, Compare, Alloc> {
	public://to decide
		typedef map<K, T, Compare, Alloc>				self_type;
		typedef K										key_type;
		typedef T										mapped_type;
		typedef ft::pair<key_type, mapped_type>			value_type;
		typedef Compare									key_compare;
		typedef ft::RBTree<K, ft::pair<K, T>, ft::FirstOfPair<K, T>, Compare, Alloc> Tree_struct;
		Tree_struct _tree;

	public:
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef typename Tree_struct::iterator			iterator;
		typedef typename Tree_struct::const_iterator	const_iterator;
		typedef typename Tree_struct::allocator_type	allocator_type;
		typedef typename Tree_struct::size_type			size_type;
		typedef typename Tree_struct::difference_type	difference_type;

	map(const Compare &c = Compare(), const Alloc &a = Alloc()) : _tree(c, a) {};

	pair<iterator, bool> insert(const value_type& val) {
		return _tree.insertUni(val);
	};

	mapped_type &operator[](const key_type& k) {
		return insert(value_type(k, mapped_type())).first->second;
	}; // F

}; // map

}; // namespace ft

#endif