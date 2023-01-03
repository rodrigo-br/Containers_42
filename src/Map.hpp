#ifndef MAP_H
#define MAP_H

//life is sucks

#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include <memory>
#include <cmath>

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
		typedef reverse_iterator<iterator> 								rev_iterator;
		typedef reverse_iterator<const_iterator> 						const_rev_iterator;

	private:
		size_type	_size;
		key_compare	_compare;
		alloc_node	_alloc;
		map_node*	_root;
		map_node*	_begin;
		map_node*	_end;

	public:
/******************************************************************************/
/*						Member class									      */
/******************************************************************************/

		class value_compare {
			protected: 
				key_compare _comp;

				value_compare(key_compare c) : _comp(c) {}; 

			private:
				value_compare() {};
			
			public:
				value_type first;
				value_type second;
				
				bool operator()(const value_type& x, const value_type& y) const {
					return _comp(x.first, y.first);
				};
		}; //class value_compare

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

	explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_size(0), _compare(comp), _alloc(alloc), _root(_alloc.allocate(1)), _begin(_alloc.allocate(1)), _end(_alloc.allocate(1)) { 
			_init_map(); 
		};

	map(const map& x) : _size(0), _compare(x._compare), _alloc(x._alloc), _root(_alloc.allocate(1)), _begin(_alloc.allocate(1)), _end(_alloc.allocate(1)) {
		_init_map();
		insert(x.begin(), x.end());
	};

	template<class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_size(0), _compare(comp), _alloc(alloc), _root(_alloc.allocate(1)), _begin(_alloc.allocate(1)), _end(_alloc.allocate(1)) {
		_init_map();
		insert(first, last);
	};

	map &operator=(const map& x) {
		if (this != &x) {
			clear();
			_compare = x._compare;
			_alloc = x._alloc;
			_size = 0;
			insert(x.begin(), x.end());
		}
		return *this;
	};

	~map() {
		if (_size == 0) {
			_alloc.destroy(_root);
			_alloc.destroy(_begin);
			_alloc.destroy(_end);
			_alloc.deallocate(_root, 1);
			_alloc.deallocate(_begin, 1);
			_alloc.deallocate(_end, 1);
		}
		else { _clear(_root); }
	};

	allocator_type get_allocator() const { return _alloc; };

/******************************************************************************/
/*						Element access									      */
/******************************************************************************/

	mapped_type &operator[](const key_type& k) {
		iterator it = find(k);
		if (it == end()) {
			it = insert(ft::make_pair(k, mapped_type())).first;
		}
		return it->second;
	};

	mapped_type &at(const Key& k) {
		iterator it = find(k);
		if (it == end()) {
			throw std::out_of_range("map::at Key not found in map");
		}
		return it->second;
	};

/******************************************************************************/
/*						Iterators										      */
/******************************************************************************/

	iterator begin() { 
		// if (empty())
		// 	return end(); not sure if needed. test it
		return iterator(_begin);
	};

	const_iterator begin() const {
		// if (empty())
		// 	return end(); not sure if needed. test it
		return const_iterator(_begin);
	 };

	iterator end() { return iterator(_end); };

	const_iterator end() const { return const_iterator(_end); };

	rev_iterator rbegin() { return rev_iterator(end()); };

	const_rev_iterator rbegin() const { return const_rev_iterator(end()); };

	rev_iterator rend() { return rev_iterator(begin()); };

	const_rev_iterator rend() const { return const_rev_iterator(begin()); };

/******************************************************************************/
/*						Capacity										      */
/******************************************************************************/

	bool empty() const { return _size == 0; };

	size_type size() const { return _size; };

	size_type max_size() const { return _alloc.max_size(); };

/******************************************************************************/
/*						Modifiers										      */
/******************************************************************************/

	void clear() { erase(begin(), end()); };

	ft::pair<iterator, bool> insert(const value_type& value) {
		bool		inserted = false;
		map_node*	new_node = NULL;
		_root = _insert(_root, NULL, value, inserted, new_node);
		_setBorders();

		if (inserted) { return ft::make_pair(iterator(new_node), false); }
		else { return ft::make_pair(iterator(new_node), true); }
	};

	iterator insert(iterator pos, const value_type& value) {
		(void)pos;
		return insert(value).first;
	};

	template<class InputIt>
	void insert(InputIt first, InputIt last) {
		while (first != last) {
			insert(*first);
			++first;
		}
	};

	void erase(iterator pos) { erase(pos->first); };

	void erase(iterator first, iterator last) {
		while (first != last) {
			iterator tmp = first;
			++first;
			erase(tmp);
		}
	};

	size_type erase(const Key& key) {
		bool first_found = false;

		_root = _deleteNode(_root, key, first_found);
		_setBorders();
		return first_found ? 1 : 0;
	};

	void swap(map& other) {
		std::swap(_root, other._root);
		std::swap(_begin, other._begin);
		std::swap(_end, other._end);
		std::swap(_size, other._size);
		std::swap(_compare, other._compare);
		std::swap(_alloc, other._alloc);
	};

/******************************************************************************/
/*						Lookup										      	  */
/******************************************************************************/

	size_type count(const Key& key) const { return find (key) != end() ? 1 : 0; };

	iterator find(const Key& key) {
		for (iterator it = begin(); it != end(); ++it) {
			if (it->first == key) { return it; }
		}
		return end();
	};

	const_iterator find(const Key& key) const {
		for (const_iterator it = begin(); it != end(); ++it) {
			if (it->first == key) { return it; }
		}
		return end();
	};

	ft::pair<iterator, iterator> equal_range(const Key& key) {
		make_pair(lower_bound(key), upper_bound(key));
	};

	ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
		const_iterator lower = lower_bound(key);
		const_iterator upper = upper_bound(key);
		make_pair(lower, upper);
	};

	iterator lower_bound(const Key& key) {
		iterator it = begin();
		while (it != end()) {
			if (!_compare(it->first, key)) { break; }
			++it;
		}
		return it;
	};

	const_iterator lower_bound(const Key& key) const {
		const_iterator it = begin();
		while (it != end()) {
			if (!_compare(it->first, key)) { break; }
			++it;
		}
		return it;
	};

	iterator upper_bound(const Key& key) {
		iterator it = begin();
		while (it != end()) {
			if (_compare(key, it->first)) { break; }
			++it;
		}
		return it;
	};

	const_iterator upper_bound(const Key& key) const {
		const_iterator it = begin();
		while (it != end()) {
			if (_compare(key, it->first)) { break; }
			++it;
		}
		return it;
	};

/******************************************************************************/
/*						Observers										      */
/******************************************************************************/

	key_compare key_comp() const { return _compare; };

	value_compare value_comp() const { return value_compare(_compare); };

/******************************************************************************/
/*						Operators										      */
/******************************************************************************/

	//(...)

	private:
/******************************************************************************/
/*					Private auxiliar functions								  */
/******************************************************************************/
	void _init_map() {
		_alloc.construct(_root, value_type());
		_alloc.construct(_begin, value_type());
		_alloc.construct(_end, value_type());

		_root->parent = _root;
		_end->parent = _root;
		_root->left = _begin;
		_root->right = _end;
	};

	map_node* _leftMost(map_node* node) {
		map_node* n = node;
		while (n != NULL && n->left != NULL && n->left != _begin) { n = n->left; }
		return n;
	};

	map_node* _rightMost(map_node* node) {
		map_node* n = node;
		while (n != NULL && n->right != NULL && n->right != _end) { n = n->right; }
		return n;
	};

	void _setBorders() {
		map_node* begin = _leftMost(_root);
		map_node* end = _rightMost(_root);

		_begin->parent = begin;
		if (begin != NULL) { begin->left = _begin; }
		_end->parent = end;
		if (end != NULL) { end->right = _end; }
	};

	map_node* _insert(map_node *node, map_node *parent, const value_type &val, bool &found, map_node* &r_node) {
		key_compare compare = _compare;

		if (_size == 0) {
			_alloc.destroy(_root);
			_alloc.deallocate(_root, 1);
			return (_newNode(val, parent, found, r_node));
		}
		else if (node == NULL || node == _begin || node == _end)
			return (_newNode(val, parent, found, r_node));
		if (compare(val.first, node->data.first))
			node->left = _insert(node->left, node, val, found, r_node);
		else if (compare(node->value.first, val.first))
			node->right = _insert(node->right, node, val, found, r_node);
		else {
			found = true;
			r_node = node;
			return node;
		}
		node->height = 1 + std::max(height(node->left), height(node->right));

		return _balance(node, val);
	};

	map_node* _newNode(const value_type &val, map_node *parent, bool &found, map_node* &r_node) {
		map_node* node = _alloc.allocate(1);
		_alloc.construct(node, val);
		node->parent = parent;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
		++_size;
		found = false;
		r_node = node;
		return node;
	};

	map_node* _balance(map_node *node, const value_type &val) {
		key_compare compare = _compare;
		int balance = (node == NULL || node == _begin || node == _end || _size == 0)
		? 0 : height(node->left) - height(node->right);

		if (balance > 1 && node->left != NULL && node->left != _begin) {
			if (compare(val.first, node->left->data.first))
				return _rotateRight(node);
			else if (compare(node->left->data.first, val.first)) {
				node->left = _rotateLeft(node->left);
				return _rotateRight(node);
			}
		}
		if (balance < -1 && node->right != NULL && node->right != _end) {
			if (compare(node->right->data.first, val.first))
				return _rotateLeft(node);
			else if (compare(val.first, node->right->data.first)) {
				node->right = _rotateRight(node->right);
				return _rotateLeft(node);
			}
		}
		return node;
	};

	map_node* _balance(map_node *root) {
		int first_h = 0;
		int second_h = 0;

		if (root->left != NULL && root->left != _begin)
			first_h = root->left->height;
		if (root->right != NULL && root->right != _end)
			second_h = root->right->height;

		if (std::abs(first_h - second_h) > 1) {
			if (first_h < second_h) {
				int first_right_h = 0;
				int second_right_h = 0;
				if (root->right->left != NULL && root->right->left != _begin)
					first_right_h = root->right->left->height;
				if (root->right->right != NULL && root->right->right != _end)
					second_right_h = root->right->right->height;
				if (first_right_h > second_right_h) {
					root->right = _rotateRight(root->right);
					return _rotateLeft(root);
				}
				root = _rotateLeft(root);
			} else {
				int first_left_h = 0;
				int second_left_h = 0;
				if (root->left->left != NULL && root->left->left != _begin)
					first_left_h = root->left->left->height;
				if (root->left->right != NULL && root->left->right != _end)
					second_left_h = root->left->right->height;
				if (first_left_h < second_left_h) {
					root->left = _rotateLeft(root->left);
					return _rotateRight(root);
				}
				root = _rotateRight(root);
			}
		}
		return root;
	};

	map_node* _rotateRight(map_node *node) {//verificar
		map_node* left = node->left;
		map_node* leftRight = left->right;

		left->right = node;
		node->left = leftRight;

		node->height = 1 + std::max(height(node->left), height(node->right));
		left->height = 1 + std::max(height(left->left), height(left->right));

		return left;
	};

	map_node* _rotateLeft(map_node *node) {//verificar
		map_node* right = node->right;
		map_node* rightLeft = right->left;

		right->left = node;
		node->right = rightLeft;

		node->height = 1 + std::max(height(node->left), height(node->right));
		right->height = 1 + std::max(height(right->left), height(right->right));

		return right;
	};

	void _clear(map_node *node) {
		if (node == NULL) { return; }
		_clear(node->left);
		_clear(node->right);
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	};

}; //class map

/******************************************************************************/
/*						Non-Member Functions								  */
/******************************************************************************/

	//(...)

}; //namespace ft

#endif