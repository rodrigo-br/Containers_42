#ifndef TESTS_H
#define TESTS_H

#include "catch.hpp"
#include "../src/vector.hpp"
#include "../src/reverse_iterator.hpp"
#include "../src/iterator_traits.hpp"
#include "../src/type_traits.hpp"
#include "../src/algorithm.hpp"
#include "../src/utility.hpp"
#include "../src/bidirectional_iterator.hpp"
#include "../src/Map.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <typeinfo>     // typeid

void print_line(void);

class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
  int* p;
public:
  MyIterator(int* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};

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
	for (size_t i = 0; i < v2.size(); i++) {
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

template<typename T>
void compare(ft::vector<T> &v1, ft::vector<T> &v2) {
	for (size_t i = 0; i < v2.size(); i++) {
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

template<typename T>
void simple_compare(ft::vector<T> &v1, std::vector<T> &v2) {
	for (size_t i = 0; i < v2.size(); i++) {
		REQUIRE(v2[i] == v1[i]);
	}
	REQUIRE(v2.size() == v1.size());
}

template<typename T>
void simple_compare(ft::vector<T> &v1, ft::vector<T> &v2) {
	for (size_t i = 0; i < v2.size(); i++) {
		REQUIRE(v2[i] == v1[i]);
	}
	REQUIRE(v2.size() == v1.size());
}

template<typename T, typename T_2>
void compare(ft::map<T, T_2> &v1, std::map<T, T_2> &v2) {
	
}

#endif