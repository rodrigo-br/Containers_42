#ifndef LIST_H
#define LIST_H

#include <memory>
#include "iterator_traits.hpp"

// No idea what i'm doing here
namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class list
	{
		public:
			typedef	T												value_type;
			typedef	Allocator										allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;


		private:
			struct Node;
			typedef typename allocator_type::template rebind<Node>::other	ANode;
			typedef typename ANode::pointer							NodePtr;
			typedef typename ANode::const_pointer					ConstNodePtr;
			struct Node
			{
				NodePtr		*prev;
				NodePtr		*next;
				value_type	data;
			};
			NodePtr													head;
			size_type												size;
			ANode													alloc;


	};
	
}; // namespace ft

#endif