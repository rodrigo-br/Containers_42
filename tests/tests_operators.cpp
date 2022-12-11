#include "catch.hpp"
#include "../src/vector.hpp"
#include <vector>

TEST_CASE ("Testando operator= com vector vazio") {
	ft::vector<int> x(5);
	ft::vector<int> y;

	y = x;
	for (size_t i = 0; i < x.size(); i++) {
		REQUIRE(y[i] == x[i]);
	}
}

TEST_CASE ("Testando operator= com vector(5)") {
	int cavalinho[] = {1, 2, 3, 4, 5};
	ft::vector<int> x(std::begin(cavalinho), std::end(cavalinho));
	ft::vector<int> y(5);

	y = x;
	for (size_t i = 0; i < x.size(); i++) {
		REQUIRE(y[i] == x[i]);
	}
}