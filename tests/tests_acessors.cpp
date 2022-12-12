#include "tests.hpp"

TEST_CASE ("Testando acessors at, front, back") {
	int array[] = {1, 2, 3, 4, 5};
	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	for (size_t i = 0; i < v1.size(); i++) {
		REQUIRE(v2.at(i) == v1.at(i));
		REQUIRE(v2.data()[i] == v1.data()[i]);
	}
	REQUIRE(v2.front() == v1.front());
	REQUIRE(v2.back() == v1.back());
}