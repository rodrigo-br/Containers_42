#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "functional.hpp"
#include "functionalExt.hpp"
#include <cstddef>
#include <utility>
#include "utility.hpp"
#include "type_traits.hpp"
#include "Container.hpp"

namespace ft{

enum Color { RED, BLACK };

template <typename Value>
struct RBNode {

	typedef			RBNode<Value>*	NodePtr;
	typedef const	RBNode<Value>*	ConstNodePtr;

	Color					color;
	NodePtr					parent;
	NodePtr					left;
	NodePtr					right;
	Value					value;

	RBNode() : value(Value()), color(RED), parent(NULL), left(NULL), right(NULL) {};

	NodePtr minimum(NodePtr x)
	{
		while (x->left != NULL)
			x = x->left;
		return x;
	};

	NodePtr maximum(NodePtr x)
	{
		while (x->right != NULL)
			x = x->right;
		return x;
	};

	ConstNodePtr minimum(ConstNodePtr x)
	{
		while (x->left != NULL)
			x = x->left;
		return x;
	};

	ConstNodePtr maximum(ConstNodePtr x)
	{
		while (x->right != NULL)
			x = x->right;
		return x;
	};

}; // RBNode

template <typename Key, typename Value, typename KeyOfValue = Identity<Key, Value>, typename Compare = less<Key>, typename Alloc = std::allocator<Value> >
class RBTree {

	private:
		typedef typename Alloc::template rebind<RBNode<Value> >::other	NodeAllocator;

	public:
		typedef			RBNode<Value>									Node;
		typedef			Node*											NodePtr;
		typedef const	Node*											ConstNodePtr;
		typedef			Key												key_type;
		typedef			Value											value_type;
		typedef			value_type*										pointer;
		typedef const	value_type*										const_pointer;
		typedef			value_type&										reference;
		typedef const	value_type&										const_reference;
		typedef			size_t											size_type;
		typedef			ptrdiff_t										difference_type;
		typedef			Alloc											allocator_type;
		template<class NPTR, class PTR, class REF> class IT;
		template<class NPTR, class PTR, class REF> friend class IT;
		typedef			IT<NodePtr, pointer, reference>						iterator;
		typedef			IT<ConstNodePtr, const_pointer, const_reference>	const_iterator;
		typedef			ft::reverse_iterator<iterator>					reverse_iterator;
		typedef			ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	NodePtr			_root;
	Compare			_comp;
	allocator_type	_alloc;
	size_type		_size;
	NodePtr			_dummy;
	NodeAllocator	_nodeAlloc;
	KeyOfValue		_keyOfValue;

	static Color getColor(ConstNodePtr x)
	{
		return (x == NULL ? BLACK : x->color);
	};

	static void setColor(NodePtr x, Color c)
	{
		if (x != NULL)
			x->color = c;
	};

	static bool isRed(ConstNodePtr x)
	{
		return (getColor(x) == RED);
	};

	static bool isBlack(ConstNodePtr x)
	{
		return (getColor(x) == BLACK);
	};

	static bool isNullOrBlack(ConstNodePtr x)
	{
		return (x == NULL || isBlack(x));
	};

	RBTree(const Compare &c = Compare(), const Alloc &a = Alloc()) :
		_root(NULL), _comp(c), _alloc(a), _size(0) {
		_dummy = _nodeAlloc.allocate(1);
		_dummy->parent = NULL;
		_dummy->left = NULL;
		_dummy->right = NULL;
		_dummy->color = BLACK;
	};

	RBTree(const RBTree &x) :
		_root(x._root), _comp(x._comp), _alloc(x._alloc) {
		_dummy = _nodeAlloc.allocate(1);
		_dummy->parent = NULL;
		_dummy->left = NULL;
		_dummy->right = NULL;
		_dummy->color = BLACK;
		this->copy(x);
	};

	NodePtr copy(ConstNodePtr x)
	{
		if (x == NULL)
		{
			return NULL;
		}
		NodePtr r = newNode(x);
		r->left = copy(x->left); setParent(r->left, r);
		r->right = copy(x->right); setParent(r->right, r);
		return r;
	};

	bool empty() const
	{
		return (_size == 0);
	};

	void copy(const RBTree &x)
	{
		if (x.empty())
		{
			return ;
		}
		_root = copy(x._root);
		_root->parent = _dummy;
		_dummy->left = leftMost(_root);
		_dummy->right = rightMost(_root);
		_size = x.size();
	};

	void setParent(NodePtr child, NodePtr parent)
	{
		if (child != NULL)
			child->parent = parent;
	};

	NodePtr leftMost(NodePtr x)
	{
		if (x == NULL)
			return NULL;
		while (x->left != NULL)
			x = x->left;
		return x;
	};

	ConstNodePtr leftMost(ConstNodePtr x) const
	{
		if (x == NULL)
			return NULL;
		while (x->left != NULL)
			x = x->left;
		return x;
	};

	NodePtr rightMost(NodePtr x)
	{
		if (x == NULL)
			return NULL;
		while (x->right != NULL)
			x = x->right;
		return x;
	};

	ConstNodePtr rightMost(ConstNodePtr x) const
	{
		if (x == NULL)
			return NULL;
		while (x->right != NULL)
			x = x->right;
		return x;
	};

	~RBTree()
	{
		this->clear();
		_nodeAlloc.deallocate(_dummy, 1);
	};

	void clear()
	{
		clear(_root);
		_dummy->left = _dummy->right = _dummy;
		_root = NULL;
		_size = 0;
	};

	void clear(NodePtr x)
	{
		if (x == NULL)
			return ;
		clear(x->left);
		clear(x->right);
		deleteNode(x);
	};

	NodePtr &getRefNode(NodePtr x)
	{
		if (x == _root)
			return _root;
		NodePtr parent = x->parent;

		return (parent->left == x ? parent->left : parent->right);
	};

	void rotateRight(NodePtr m)
	{
		NodePtr &rp = this->getRefNode(m);

		rp = m->left;
		m->left = rp->right;
		rp->right = m;
		if (m->left != NULL)
			m->left->parent = m;
		rp->parent = m->parent;
		m->parent = rp;
	};

	void rotateLeft(NodePtr n)
	{
		NodePtr &rp = this->getRefNode(n);

		rp = n->right;
		n->right = rp->left;
		rp->left = n;
		if (n->right != NULL)
			n->right->parent = n;
		rp->parent = n->parent;
		n->parent = rp;
	};

	void adjustInsert(NodePtr r)
	{
		if (r == _root)
		{
			this->setColor(r, BLACK);
			return ;
		}
		if (this->isBlack(r->parent))
			return ;

		NodePtr gramma = r->parent->parent;
		NodePtr pr = gramma->right;
		NodePtr pl = gramma->left;

		if (this->isNullOrBlack(pl) || this->isNullOrBlack(pr))
		{
			if (this->isNullOrBlack(pl))
			{
				if (pr->left == r)
					this->rotateRight(pr);
				this->rotateLeft(gramma);
			}
			else
			{
				if (pl->right == r)
					this->rotateLeft(pl);
				this->rotateRight(gramma);
			}
			this->setColor(gramma, RED);
			this->setColor(gramma->parent, BLACK);
		}
		else
		{
			this->setColor(pl, BLACK);
			this->setColor(pr, BLACK);
			if (gramma != _root)
			{
				this->setColor(gramma, RED);
				this->adjustInsert(gramma);
			}
		}	
	};

	ft::pair<iterator, bool> insertUni(const Value &v)
	{
		pair<iterator, bool> res = insertNode<false>(v);

		if (res.second)
			adjustInsert(getNode(res.first));
		return res;
	};

	iterator insertMulti(const Value &v)
	{
		iterator res = insertNode<true>(v).first;

		adjustInsert(getNode(res));
		return res;
	};

	NodePtr getNode(iterator i)
	{
		return i.current;
	};

	iterator getIterator(NodePtr p)
	{
		return iterator(p);
	};

	template<bool MULTI>
	pair<iterator, bool> insertNode(const Value &e) {
		NodePtr r;

		if (_root == NULL)
		{
			r = _root = _dummy->left = _dummy->right = newNode(_dummy, e);
		}
		else
		{
			r = _root;
			for (;;)
			{
				if (_comp(key(e), key(r->value)))
				{
					if (r->left != NULL)
					{
						r = r->left;
					}
					else
					{
						r = insertLeft(r, e);
						break;
					}
				}
				else if (MULTI || _comp(key(r->value), key(e)))
				{
						if (r->right != NULL)
						{
							r = r->right;
						}
						else
						{
							r = insertRight(r, e);
							break;
						}
				}
				else
				{
					return pair<iterator,bool>(getIterator(r), false);
				}
			}
		}
		++_size;
		return pair<iterator, bool>(getIterator(r), true);
	};

	NodePtr insertLeft(NodePtr r, const Value &e)
	{
		r->left = newNode(r, e);
		if (r == _dummy->left)
			_dummy->left = r->left;
		return r->left;
	};

	NodePtr insertRight(NodePtr r, const Value &e)
	{
		r->right = newNode(r, e);
		if (r == _dummy->right)
			_dummy->right = r->right;
		return r->right;
	};

	const Key &key(const Value &e)
	{
		return _keyOfValue(e);
	};

	NodePtr newNode(NodePtr p, const Value &e)
	{
		NodePtr n = _nodeAlloc.allocate(1);

		_alloc.construct(&n->value, e);
		n->left = n->right = NULL;
		n->parent = p;
		setColor(n, RED);
		return n;
	};

	NodePtr newNode(ConstNodePtr p)
	{
		NodePtr n = _nodeAlloc.allocate(1);

		_alloc.construct(&n->value, p->value);
		setColor(n, getColor(p));
		return n;
	};

	void deleteNode(NodePtr n)
	{
		if (n != NULL)
		{
			_alloc.destroy(&n->value);
			_nodeAlloc.deallocate(n, 1);
		}
	};

	size_type erase_key(const Key &k)
	{
		if (count(k))
		{
			erase(find(k));
			return 1;
		}
		return 0;
	};

	void erase(iterator i)
	{
		NodePtr p = getNode(i);
		if (p == _dummy->left)
		{
			_dummy->left = getNode(++iterator(i));
		}
		if (p == _dummy->right)
		{
			_dummy->right = getNode(--iterator(i));
		}
		if (p->left != NULL && p->right != NULL)
		{
			changeNodes(p, rightMost(p->left));
		}
		eraseInLeaf(getRefNode(p));
		--_size;
	};

	NodePtr getPrevious(NodePtr p) const
	{
		return rightMost(p->left);
	};

	void changeNodes(NodePtr x, NodePtr y)
	{
		NodePtr yp = y->parent;
		NodePtr xl = x->left;
		getRefNode(x) = y;
		y->parent = x->parent;
		x->left = y->left;
		if (x->left)
		{
			x->left->parent = x;
		}
		y->right = x->right;
		y->right->parent = y;
		if (xl != y)
		{
			yp->right = x;
			x->parent = yp;
		}
		else
		{
			xl = x;
		}
		y->left = xl;
		xl->parent = y;
		x->right = NULL;
		Color c = getColor(x);
		setColor(x, getColor(y));
		setColor(y, c);
	};

	

	void eraseInLeaf(NodePtr &r)
	{
		if (isRed(r) || size() == 1)
		{
			deleteNode(r);
			r = NULL;
			return ;
		}
		if (!isNullOrBlack(r->right) || !isNullOrBlack(r->left))
		{
			NodePtr rem = r;
			if (isNullOrBlack(r->left))
			{
				r = r->right;
			}
			else
			{
				r = r->left;
			}
			r->parent = rem->parent;
			deleteNode(rem);
			setColor(r, BLACK);
		}
		else
		{
			NodePtr parent = r->parent;
			deleteNode(r);
			r = NULL;
			rebalance(parent, NULL);
		}
	};

	void rebalance(NodePtr parent, NodePtr r)
	{
		if (r == _root)
		{
			return;
		}
		if (parent->left == r)
		{
			rebalanceLeft(parent);
		}
		else
		{
			rebalanceRight(parent);
		}
	};

	void rebalanceRight(NodePtr r)
	{
		NodePtr pl = r->left;
		if (isRed(pl))
		{
			rotateRight(r);
			setColor(pl, BLACK);
			setColor(r, RED);
			pl = r->left;
		}
		if (isNullOrBlack(pl->left) && isNullOrBlack(pl->right))
		{
			setColor(pl, RED);
			if (isRed(r))
			{
				setColor(r, BLACK);
			}
			else
			{
				rebalance(r->parent, r);
			}
		}
		else
		{
			if (isNullOrBlack(pl->left))
			{
				rotateLeft(pl);
			}
			rotateRight(r);
			setColor(r->parent, getColor(r));
			setColor(r->parent->left, BLACK);
			setColor(r, BLACK);
		}
	};

	void rebalanceLeft(NodePtr r)
	{
		NodePtr pr = r->right;
		if (isRed(pr))
		{
			rotateLeft(r);
			setColor(pr, BLACK);
			setColor(r, RED);
			pr = r->right;
		}
		if (isNullOrBlack(pr->left) && isNullOrBlack(pr->right))
		{
			setColor(pr, RED);
			if (isRed(r))
			{
				setColor(r, BLACK);
			}
			else
			{
				rebalance(r->parent, r);
			}
		}
		else
		{
			if (isNullOrBlack(pr->right))
			{
				rotateRight(pr);
			}
			rotateLeft(r);
			setColor(r->parent, getColor(r));
			setColor(r->parent->right, BLACK);
			setColor(r, BLACK);
		}
	};

	void printOn(std::ostream &o, ConstNodePtr r, int i)
	{
		if (r == NULL)
		{
			return;
		}
		printOn(o, r->left, i + 1);
		for (int j = 0; j < i; j++)
		{
			o << "\t";
		}
		if (isRed(r))
		{
			o << "\033[1m\033[31m";
		}
		else o << "\033[1m\033[30m";
		o << r->value.first << "\033[0m" << std::endl;
		printOn(o, r->right, i + 1);
	};

	size_t size(void) const
	{
		return _size;
	};

	void printOn(std::ostream &o)
	{
		printOn(o, _root, 1);
	};

	void prettyPrint()
	{
		if (_root)
		{
			printHelper(_root, "", true);
		}
	};

	void printHelper(NodePtr root, std::string indent, bool test)
	{
		if (root != NULL)
		{
			std::cout << indent;
			if (test)
			{
				std::cout << "----";
				indent += "     ";
			}
			else
			{
				std::cout << "----";
				indent += "|    ";
			}
		
		std::string sColor = isRed(root) ? "\033[1m\033[31m" : "\033[1m\033[30m";
		std::cout << sColor << root->value.first << "\033[0m" << std::endl;
		printHelper(root->left, indent, false);
		printHelper(root->right, indent, true);
		}
	};

	void swap(RBTree &x)
	{
		if (this == &x)
			return;
		if (_alloc == x._alloc)
		{
			std::swap(_root, x._root);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
			std::swap(_size, x._size);
			std::swap(_dummy, x._dummy);
			std::swap(_nodeAlloc, x._nodeAlloc);
			std::swap(_keyOfValue, x._keyOfValue);
		}
		else
		{
			std::swap(*this, x);
		}
	};

	iterator end()
	{
		return _dummy;
	};

	const_iterator end() const
	{
		return _dummy;
	};

	iterator begin()
	{
		return _dummy->left;
	};

	const_iterator begin() const
	{
		return _dummy->left;
	};

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	};

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	};

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	};

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	};

	Compare key_comp() const
	{
		return _comp;
	};

	iterator find(const Key &k)
	{
		NodePtr ptr = _root;
		while (ptr != NULL)
		{
			if (_comp(k, _keyOfValue(ptr->value)))
			{
				ptr = ptr->left;
			}
			else if (_comp(_keyOfValue(ptr->value), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return ptr;
			}
		}
		return end();
	};

	size_type count(const Key &k) const
	{
		NodePtr ptr = _root;
		while (ptr != NULL)
		{
			if (_comp(k, _keyOfValue(ptr->value)))
			{
				ptr = ptr->left;
			}
			else if (_comp(_keyOfValue(ptr->value), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return 1;
			}
		}
		return 0;
	};

	ft::pair<iterator, iterator> equal_range(const Key &k)
	{
		return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	};

	ft::pair<const_iterator, const_iterator> equal_range(const Key &k) const
	{
		return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	};

	iterator lower_bound(const Key &k)
	{
		NodePtr ptr = _root;
		NodePtr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, _keyOfValue(ptr->value)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(_keyOfValue(ptr->value), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return ptr;
			}
		}
		return res;
	};

	const iterator lower_bound(const Key &k) const
	{
		NodePtr ptr = _root;
		NodePtr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, _keyOfValue(ptr->value)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(_keyOfValue(ptr->value), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return ptr;
			}
		}
		return res;
	};

	iterator upper_bound(const Key &k)
	{
		NodePtr ptr = _root;
		NodePtr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, _keyOfValue(ptr->value)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(_keyOfValue(ptr->value), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return ptr->right;
			}
		}
		return res;
	};

	const iterator upper_bound(const Key &k) const
	{
		NodePtr ptr = _root;
		NodePtr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, _keyOfValue(ptr->value)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(_keyOfValue(ptr->value), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return ptr->right;
			}
		}
		return res;
	};

}; // RBTree

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
template <class NodePtr, class PTR, class REF>
class RBTree<Key, Value, KeyOfValue, Compare, Alloc>::IT : public ft::iterator<ft::bidirectional_iterator_tag,
Key, typename Alloc::difference_type, PTR, REF>
{
	friend class RBTree<Key, Value, KeyOfValue, Compare, Alloc>;
	
	public:
	NodePtr current;
	private:
	void inc()
	{
		if (current && current->right == NULL)
		{
			NodePtr ptr = current;
			while ((current = current->parent)->right == ptr)
			{
				ptr = current;
			}
		}
		else
		{
			current = leftMost(current->right);
		}
	};

	NodePtr rightMost(NodePtr x)
	{
		while (x->right != NULL)
		{
			x = x->right;
		}
		return x;
	};

	void dec()
	{
		if (current->left == NULL)
		{
			NodePtr ptr = current;
			while ((current = current->parent)->left == ptr)
			{
				ptr = current;
			}
		}
		else
		{
			if (current->parent == current)
			{
				current = current->right;
			}
			else
			{
				current = rightMost(current->left);
			}
		}
	};

	NodePtr leftMost(NodePtr x)
	{
		while (x->left != NULL)
		{
			x = x->left;
		}
		return x;
	};

	IT(NodePtr x) : current(x) {};

	public:
		IT() {};
		template<class NP, class P, class R>
		IT(IT<NP, P, R> i) : current(i.current) {};
		IT &operator++() { inc(); return *this; };
		IT &operator--() { dec(); return *this; };
		IT operator++(int) { IT i(*this); inc(); return i; };
		IT operator--(int) { IT i(*this); dec(); return i; };
		REF operator*() const { return current->value; };
		PTR operator->() const { return &(operator*()); };
		bool operator==(IT &x) const { return current == x.current; };
		bool operator!=(IT &x) const { return !(*this == x); };
};// IT

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
bool operator==(const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &x, const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &y)
{
	return (x.size() == y.size());
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
bool operator!=(const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &x, const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &y)
{
	return (!(x == y));
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
bool operator<(const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &x, const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &y)
{
	return (x.size() < y.size());
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
bool operator>(const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &x, const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &y)
{
	return (y < x);
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
bool operator>=(const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &x, const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &y)
{
	return (!(x < y));
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
bool operator<=(const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &x, const RBTree<Key, Value, KeyOfValue, Compare, Alloc> &y)
{
	return (!(y < x));
};


}; // namespace ft
#endif