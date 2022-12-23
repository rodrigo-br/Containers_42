#ifndef LIST_H
#define LIST_H

#include <memory>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "list_iterator.hpp"

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
			typedef typename ft::list_iterator<value_type>			iterator;
			typedef typename ft::list_iterator<const value_type>	const_iterator;

		private:
			struct Node;
			typedef typename
			allocator_type::template rebind<Node>::other			ANode;
			typedef typename ANode::pointer							NodePtr;
			typedef typename ANode::const_pointer					ConstNodePtr;
			NodePtr													_head;
			size_type												_size;
			ANode													_alloc;
			struct Node
			{
				NodePtr		*prev;
				NodePtr		*next;
				value_type	data;
			};

			NodePtr newNode(void) {
				NodePtr node = _alloc.allocate(1);
				node->prev = node;
				node->next = node;
				return node;
			};

			NodePtr newNode(NodePtr suc, const value_type &val) {
				NodePtr node = _alloc.allocate(1);
				_alloc.construct(&(node->data), val);
				NodePtr prev = suc->prev;
				node->next = suc;
				node->prev = prev;
				prev->next = suc->prev = node;
				return node;
			};

			void deleteNode(NodePtr node) {};
			void moveInAlloc(iterator pos, iterator first, iterator last) {};
			void move(iterator pos, iterator first, iterator last) {};

		public:
			inline list(const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _head(newNode()), _size(0) {};
	
			explicit list(size_type n, const value_type &val = value_type(),
							const allocator_type &alloc = allocator_type()) {};
			list(const list &lst) {};
			~list() { clear(); _alloc.deallocate(_head, 1); };

			template<class InputIterator>
			void assign(InputIterator first, InputIterator last,
						const allocator_type &alloc = allocator_type(),
						typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {};
			
			list &operator=(const list &lst) {};

			iterator begin() { return iterator(_head->next); };
			const_iterator begin() const { return const_iterator(_head->next); };
			iterator end() { return iterator(_head); };
			const_iterator end() const { return const_iterator(_head); };

			size_type size() const { return _size; };
			bool empty() const { return _size == 0; };
			const value_type &get_allocator() const { return _alloc; };
			reference front() { return *begin(); };
			const_reference front() const { return *begin(); };
			reference back() { return *(--end()); };
			const_reference back() const { return *(--end()); };

			iterator insert(iterator pos, const value_type &val = value_type()) {};

			template<class InputIterator>
			void insert(iterator pos, InputIterator first, InputIterator last,
						typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {};

			void push_front(const value_type &val) { insert(begin(), val); };
			void push_back(const value_type &val) { insert(end(), val); };
			iterator erase(iterator pos) {};
			iterator erase(iterator first, iterator last) {};
			void pop_front() { erase(begin()); };
			void pop_back() { erase(--end()); };
			void clear() { erase(begin(), end()); };
			void swap(list &lst) {};
			void merge(list &lst) {};
			void splice(iterator pos, list &lst) {};
			void splice(iterator pos, list &lst, iterator first) {};
			void splice(iterator pos, list &lst, iterator first, iterator last) {};
			void sort()	{};
	};
	
}; // namespace ft

#endif