#ifndef MAP_H
#define MAP_H

#include "RBTree.hpp"

namespace ft {

template <class K, class T> struct FirstOfPair {
	const K &operator()(const pair<K, T> &p) const { return p.first; };
};

#define CONTAINER RBTree<K,pair<K,T>,FirstOfPair<K,T>,Cmp,A>
template <class K, class T, class Cmp = less<K>, 
          class A = std::allocator< pair<K,T> > >
	class map: public CONTAINER {
	public:
		typedef K 							key_type;
		typedef T 							mapped_type;
		typedef pair<const K, T> 			value_type;
		typedef Cmp 						key_compare;
		typedef typename A::reference 		reference;
		typedef typename A::const_reference const_reference;
		typedef typename A::pointer 		pointer;
		typedef typename A::const_pointer 	const_pointer;
		CONTAINER							tree_type;
		IMPORT_TYPE(iterator);
		IMPORT_TYPE(const_iterator);
		IMPORT_TYPE(RBNodePtr);
		IMPORT_TYPE(AllocRBNode);

		class value_compare : public std::binary_function<value_type, value_type, bool> {
			private:
				value_compare() {};
			protected:
				key_compare cmp;
				value_compare(Cmp c) : cmp(c) {};
			public:
				bool operator()(const value_type &x, const value_type &y) const {
					return cmp(x.first, y.first);
				};
		}; //class value_compare

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

		map() : CONTAINER(), tree_type() {};

		explicit map(const key_compare &comp, const A &alloc = A()) :
			CONTAINER(comp, alloc) {};

		map(const map &other) : tree_type(other.tree_type) {};

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const A &alloc = A()) : CONTAINER(first, last, comp, alloc) {
				tree_type.insert_range(first, last);
			};

		~map() {};

/******************************************************************************/
/*								Modifiers								      */
/******************************************************************************/

		std::pair<iterator, bool> insert( const value_type& value ) {
			return tree_type.insertUni(value);
		};

		iterator insert(iterator pos, const value_type& value) {};

		template<class InputIt> void insert(InputIt first, InputIt last) {};


		
	}; //class map
	#undef CONTAINER

}; //namespace


#endif