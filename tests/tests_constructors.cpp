#include "catch.hpp"
#include "../src/vector.hpp"
#include <vector>

void print_line(void) {
	std::cout << std::string(42, '-') << std::endl;
}

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

TEST_CASE ("Passando array de String first e last no constructor") {
	print_line();
		std::string cavalinho[] = {"cavalinho", "na", "chuva", "ao", "vento"};
		ft::vector<std::string> v(std::begin(cavalinho), std::end(cavalinho));
		std::vector<std::string> v2(std::begin(cavalinho), std::end(cavalinho));

		compare(v, v2);
}

TEST_CASE ("Passando array de int first e last no constructor") {
		int cavalinho[] = {1, 2, 3, 4, 5};
		ft::vector<int> v(std::begin(cavalinho), std::end(cavalinho));
		std::vector<int> v2(std::begin(cavalinho), std::end(cavalinho));

		compare(v, v2);
}

TEST_CASE ("Passando <int> size 5 no constructor") {
		ft::vector<int> v(5);
		std::vector<int> v2(5);

		compare(v, v2);
}

TEST_CASE ("Passando int no constructor vazio") {
		ft::vector<int> v;
		std::vector<int> v2;

		compare(v, v2);
}
