#ifndef UTILITY_H
#define UTILITY_H

namespace ft {
	template <class T1, class T2>
	struct pair {
		T1 first;
		T2 second;
		pair() : first(T1()), second(T2()) {};
		pair(const T1& x, const T2& y) : first(x), second(y) {};
	};

	// template <class T1, class T2>
	// pair<T1, T2> make_pair( T1 t, T2 u ) {
	// 	return (ft::pair<T1, T2>(t, u));
	// };

}; //namespace ft

#endif