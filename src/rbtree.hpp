#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "functional.hpp"
#include "functionalExt.hpp"
#include "utility.hpp"
#include "type_traits.hpp"
#include "Container.hpp"

namespace ft{

static class nullptr_t
{
	public:
		template<class T> operator T*() const { return (0); }
		template<class C, class T> operator T C::*() const { return (0); }
	private:
		void operator&() const;

} _nullptr = {};

enum Color { RED, BLACK };

template <typename Value>
struct RBNode {

	typedef			RBNode<Value>*	NodePtr;
	typedef const	RBNode<Value>*	ConstNodePtr;

	Color					color;
	NodePtr					*parent;
	NodePtr					*left;
	NodePtr					*right;
	Value					value;

	RBNode() : value(Value()), color(RED), parent(_nullptr), left(_nullptr), right(_nullptr) {};

	NodePtr minimum(NodePtr x)
	{
		while (x->left != _nullptr)
			x = x->left;
		return x;
	};

	NodePtr maximum(NodePtr x)
	{
		while (x->right != _nullptr)
			x = x->right;
		return x;
	};

	ConstNodePtr minimum(ConstNodePtr x)
	{
		while (x->left != _nullptr)
			x = x->left;
		return x;
	};

	ConstNodePtr maximum(ConstNodePtr x)
	{
		while (x->right != _nullptr)
			x = x->right;
		return x;
	};

}; // RBNode

template <typename Key, typename Value, typename KeyOfValue = ft::Identity<Key, Value>, typename Compare = less<Key>, typename Alloc = std::allocator<Value> >
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
		typedef			ft::bidirectional_iterator<NodePtr>				iterator;
		typedef			ft::bidirectional_iterator<ConstNodePtr>		const_iterator;
		typedef			ft::reverse_iterator<iterator>					reverse_iterator;
		typedef			ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	NodePtr			_root;
	NodePtr			_dummy;
	size_type		_size;
	Compare			_comp;
	NodeAllocator	_nodeAlloc;
	allocator_type	_alloc;

	static Color getColor(ConstNodePtr x)
	{
		return (x == _nullptr ? BLACK : x->color);
	};

	static void setColor(NodePtr x, Color c)
	{
		x->color = c;
	};

	static bool isRed(ConstNodePtr x)
	{
		return (this->getColor(x) == RED);
	};

	static bool isBlack(ConstNodePtr x)
	{
		return (this->getColor(x) == BLACK);
	};

	static bool isNullOrBlack(ConstNodePtr x)
	{
		return (x == _nullptr || this->isBlack(x));
	};

	RBTree(const Compare &c = Compare(), const Alloc &a = Alloc()) :
		_root(_nullptr), _comp(c), _alloc(a), _size(0) {
		_dummy = _nodeAlloc.allocate(1);
		_dummy->parent = _nullptr;
		_dummy->left = _nullptr;
		_dummy->right = _nullptr;
		_dummy->color = BLACK;
	};

	RBTree(const RBTree &x) :
		_root(x._root), _comp(x._comp), _alloc(x._alloc) {
		this->copy(x);
	};

	~RBTree() {
		this->clear();
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
		if (m->left != _nullptr)
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
		if (n->right != _nullptr)
			n->right->parent = n;
		rp->parent = n->parent;
		n->parent = rp;
	};

}; // RBTree

}; // namespace ft
#endif