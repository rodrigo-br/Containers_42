#ifndef UTILITY_H
#define UTILITY_H

namespace ft {
	template<class U, class V>
	struct pair {
		U first;
		V second;
		pair() : first(U()), second(V()) {};
		pair(const U &u, const V &v) : first(u), second(v) {};
	};

	template<class U, class V>
	pair<U, V> make_pair(const U &u, const V &v) {
		return pair<U, V>(u, v);
	};

}; //namespace ft

#endif