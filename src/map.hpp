#ifndef MAP_HPP
# define MAP_HPP

#include <limits>
#include "rbtree.hpp"

namespace ft {

template <class K, class T, class Compare = less<K>, class Alloc = std::allocator<ft::pair<K, T> > >
class map : public ft::RBTree<K, ft::pair<K, T>, ft::FirstOfPair<K, T>, Compare, Alloc> {
	public://to decide
		typedef map<K, T, Compare, Alloc>				self_type;
		typedef K										key_type;
		typedef T										mapped_type;
		typedef ft::pair<K, T>							value_type;
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
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		allocator_type _alloc;

	public:
		class value_compare : std::binary_function<value_type, value_type, bool>
		{
			friend class map;

			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {};

			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}
		};

	map() : _tree(Compare(), Alloc()) {};

	map(const Compare &c, const Alloc &a = Alloc()) : _tree(c, a) {};

	~map()
	{
		clear();
	};

	pair<iterator, bool> insert(const value_type& val)
	{
		return _tree.insertUni(val);
	};

	T &operator[](const K& key)
	{
		return insert(value_type(key, mapped_type())).first->second;
	};

	allocator_type get_allocator() const
	{
		return _tree._alloc;
	};

	bool empty() const
	{
		return _tree.empty();
	};

	size_type size() const
	{
		return _tree.size();
	};

	void clear()
	{
		_tree.clear();
	};

	void swap(map& other)
	{
		_tree.swap(other._tree);
	};

	iterator begin()
	{
		return _tree.begin();
	};

	const_iterator begin() const
	{
		return _tree.begin();
	};

	iterator end()
	{
		return _tree.end();
	};

	const_iterator end() const
	{
		return _tree.end();
	};

	reverse_iterator rbegin()
	{
		return _tree.rbegin();
	};

	const_reverse_iterator rbegin() const
	{
		return _tree.rbegin();
	};

	reverse_iterator rend()
	{
		return _tree.rend();
	};

	const_reverse_iterator rend() const
	{
		return _tree.rend();
	};

	// key_compare key_comp() const
	// {
	// 	return key_compare();
	// };

	// value_compare value_comp() const
	// {
	// 	return value_compare();
	// };



}; // map

}; // namespace ft

#endif