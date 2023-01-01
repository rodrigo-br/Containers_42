#ifndef MAP_H
#define MAP_H

#include "RBTree.hpp"

namespace ft {

template <class K, class T> struct FirstOfPair {
	const K &operator()(const pair<K, T> &p) const { return p.first; };
};

#define CONTAINER  RBTree<K,pair<K,T>,FirstOfPair<K,T>,Cmp,A>
template <class K, class T, class Cmp = less<K>, 
          class A = std::allocator< pair<K,T> > >
class map: public CONTAINER {
public:
	IMPORT_TYPE(value_type); IMPORT_TYPE(iterator);
	typedef T                          mapped_type;
	map(const Cmp &c=Cmp(), const A &a=A() ) : CONTAINER(c, a) {}
	pair<iterator,bool> insert(const value_type &value) 
		{ return CONTAINER::insertUni(value); }
	T &operator[](const K &key)
		{ return insert(value_type(key, T())).first->second; }
};

#undef CONTAINER

// Exemplo 7.5 - Template de classes multimap

} // namespace


#endif