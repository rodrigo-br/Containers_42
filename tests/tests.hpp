#ifndef TESTS_H
#define TESTS_H

#include "catch.hpp"
#include "../src/vector.hpp"
// #include "../src/reverse_iterator.hpp"
// #include "../src/iterator_traits.hpp"
#include <vector>
#include <iostream>

void print_line(void);

template<typename T>
void print_vector(ft::vector<T> &v) {
	std::cout << "Meu: \n";
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v[i] << "\n";
	}
	print_line();
}

template<typename T>
void print_vector(std::vector<T> &v) {
	std::cout << "Dele:\n";
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v[i] << "\n";
	}
	print_line();
}

/**
 * @brief Test if the values inside the two vectors are equal. Also test
 * the functions: size(), capacity(), max_size(), empty(), reserve(),
 * shrink_to_fit() and get_allocator()
 * 
 * @tparam T the type template of the vectors to be tested.
 * This param is implic, just make sure the 2 vectors have the same template type
 * @param v1 my ft implementation of vector
 * @param v2 the original vector from std::c++98
 */
template<typename T>
void compare(ft::vector<T> &v1, std::vector<T> &v2) {
	for (size_t i = 0; i < v1.size(); i++) {
		REQUIRE(v2[i] == v1[i]);
	}
	REQUIRE(v2.size() == v1.size());
	REQUIRE(v2.capacity() == v1.capacity());
	REQUIRE(v2.max_size() == v1.max_size());
	REQUIRE(v2.empty() == v1.empty());
	v1.reserve(10);
	v2.reserve(10);
	REQUIRE(v2.capacity() == v1.capacity());
	v2.shrink_to_fit();
	v1.shrink_to_fit();
	REQUIRE(v2.capacity() == v1.capacity());
	REQUIRE(v2.get_allocator() == v1.get_allocator());
}

#endif