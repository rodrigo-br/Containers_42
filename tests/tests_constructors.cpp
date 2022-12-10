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
void compare(ft::vector<T> &v, std::vector<T> &v2) {
	for (size_t i = 0; i < v.size(); i++) {
		REQUIRE(v2[i] == v[i]);
	}
	REQUIRE(v2.size() == v.size());
	REQUIRE(v2.capacity() == v.capacity());
	REQUIRE(v2.max_size() == v.max_size());
	REQUIRE(v2.empty() == v.empty());
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