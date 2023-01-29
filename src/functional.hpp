#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

namespace ft {

template<class T>
struct less {
	bool operator()(const T &x, const T &y)	const { return x < y; } 
};

template<class T>
struct greater {
	bool operator()(const T &x, const T &y)	const { return x > y; } 
};

template<class T>
struct equal_to {
	bool operator()(const T &x, const T &y)	const { return x == y; } 
};

} // namespace aed.

#endif
