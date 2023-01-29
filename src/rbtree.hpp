#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include "bidirectional_iterator.hpp"
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

template <typename Key, typename Value, typename KeyOfValue, typename Compare = less<Key>, typename Alloc = std::allocator<Value> >
class RBTree {
	// agora vai, menó...

}; // RBTree

#endif