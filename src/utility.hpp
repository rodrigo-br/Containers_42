#ifndef UTILITY_H
#define UTILITY_H

namespace ft {
	template <class T1, class T2>
    struct pair
    {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(T1()), second(T2()) {};

        template <class U, class V>
        pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {};

		pair(const first_type &a, const second_type &b) : first(a), second(b) {};
    };

	template <class T1, class T2>
	pair<T1, T2> make_pair( T1 t, T2 u ) {
		return (ft::pair<T1, T2>(t, u));
	};

}; //namespace ft

#endif