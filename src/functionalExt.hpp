#ifndef FUNCTIONAL_EXT_HPP
#define FUNCTIONAL_EXT_HPP

#include "utility.hpp"

namespace ft {

template<class K, class V = K> 
struct Identity {
	const K &operator()(const V &v) const { return v; }
};

template <class K, class T> 
struct FirstOfPair {
	const K &operator()(const pair<K,T> &p) const
		{ return p.first; }
};

} // namespace aed.

#endif
