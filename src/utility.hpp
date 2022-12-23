#ifndef UTILITY_H
#define UTILITY_H

namespace ft {
	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(T1()), second(T2()) {};

		pair(const T1& a, const T2& b) : first(a), second(b) {};

		template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {};

		pair& operator= (const pair& pr) {
			first = pr.first;
			second = pr.second;
			return *this;
		};
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair( T1 t, T2 u ) {
		return (ft::pair<T1, T2>(t, u));
	};

}; //namespace ft

#endif