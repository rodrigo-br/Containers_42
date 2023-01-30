#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "functional.hpp"
#include "functionalExt.hpp"
#include <cstddef>
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
	NodePtr					parent;
	NodePtr					left;
	NodePtr					right;
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
		typedef			ft::bidirectional_iterator<NodePtr>				iterator;
		typedef			ft::bidirectional_iterator<ConstNodePtr>		const_iterator;
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
		return (x == _nullptr ? BLACK : x->color);
	};

	static void setColor(NodePtr x, Color c)
	{
		if (x != _nullptr)
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
		return (x == _nullptr || isBlack(x));
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

	NodePtr copy(ConstNodePtr x)
	{
		if (x == _nullptr)
		{
			return _nullptr;
		}
		NodePtr r = newNode(x);
		r->left = copy(x->left); setParent(r->left, r);
		r->right = copy(x->right); setParent(r->right, r);
		return r;
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
		if (child != _nullptr)
			child->parent = parent;
	};

	NodePtr leftMost(NodePtr x)
	{
		while (x->left != _nullptr)
			x = x->left;
		return x;
	};

	NodePtr rightMost(NodePtr x)
	{
		while (x->right != _nullptr)
			x = x->right;
		return x;
	};

	~RBTree()
	{
		this->clear();
	};

	void clear()
	{
		clear(_root);
		_dummy->left = _dummy->right = _dummy;
		_root = _nullptr;
		_size = 0;
	};

	void clear(NodePtr x)
	{
		if (x == _nullptr)
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

	void adjustInsert(NodePtr r)
	{
		if (r == _root)
		{
			this->setColor(r, BLACK);
			return ;
		}
		if (this->isBlack(r->parent))
			return ;

		NodePtr y = r->parent->parent;
		NodePtr pr = y->right;
		NodePtr pl = y->left;

		if (this->isNullOrBlack(pl) && this->isNullOrBlack(pr))
		{
			if (this->isNullOrBlack(pl))
			{
				if (pr->left == r)
					this->rotateRight(pr);
				this->rotateLeft(y);
			}
			else if (this->isNullOrBlack(pr))
			{
				if (pl->right == r)
					this->rotateLeft(pl);
				this->rotateRight(y);
			}
			this->setColor(y, RED);
			this->setColor(y->parent, BLACK);
		}
		else
		{
			this->setColor(pl, BLACK);
			this->setColor(pr, BLACK);
			if (y != _root)
			{
				this->setColor(y, RED);
				this->adjustInsert(y);
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
		return i._ptr;
	}

	iterator getIterator(NodePtr p)
	{
		return iterator(p);
	}

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
	}

	NodePtr newNode(NodePtr p, const Value &e)
	{
		NodePtr n = _nodeAlloc.allocate(1);

		_alloc.construct(&n->value, e);
		n->left = n->right = _nullptr;
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
		_alloc.destroy(&n->value);
		_nodeAlloc.deallocate(n, 1);
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
		if (p->left != _nullptr && p->right != _nullptr)
		{
			changeNodes(p, rightMost(p->left));
		}
		eraseInLeaf(getRefNode(p));
		--_size;
	}

	NodePtr getPrevious(NodePtr p)
	{
		return rightMost(p->left);
	}

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
		x->right = _nullptr;
		Color c = getColor(x);
		setColor(x, getColor(y));
		setColor(y, c);
	};

	void eraseInLeaf(NodePtr &r)
	{
		if (isRed(r) || size() == 1)
		{
			deleteNode(r);
			r = _nullptr;
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
			r = _nullptr;
			rebalance(parent, _nullptr);
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
		if (r == _nullptr)
		{
			return;
		}
		printOn(o, r->left, i + 1);
		for (int j = 0; j < i; j++)
		{
			o << " ";
		}
		if (isRed(r))
		{
			o << "\033[1m\033[31m";
		}
		else o << "\033[1m\033[30m";
		o << " " << r->value.first << "\033[0m" << std::endl;
		printOn(o, r->right, i + 1);
	};

	size_t size(void) const
	{
		return _size;
	}

	void printOn(std::ostream &o)
	{
		printOn(o, _root, 1);
	}

	void prettyPrint()
	{
		if (_root)
		{
			printHelper(_root, "", true);
		}
	};

	void printHelper(NodePtr root, std::string indent, bool test)
	{
		if (root != _nullptr)
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
		}
		std::string sColor = isRed(root) ? "RED" : "BLACK";
		std::cout << root->value.first << "(" << sColor << ")" << std::endl;
		printHelper(root->left, indent, false);
		printHelper(root->right, indent, true);
	}

}; // RBTree

}; // namespace ft
#endif