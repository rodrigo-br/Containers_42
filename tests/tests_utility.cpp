#include "tests.hpp"

TEST_CASE("Testando Pair e Make Pair") {
	int n = 1;
	int a[5] = {1, 2, 3, 4, 5};
 
    // build a pair from two ints
	auto p1 = std::make_pair(n, a[1]);
	ft::pair<int, int> p2 = ft::make_pair(n, a[1]);
	REQUIRE(p1.first == p2.first);
	REQUIRE(p1.second == p2.second);
 
	// build a pair from a reference to int and an array (decayed to pointer)
	auto p3 = std::make_pair(std::ref(n), a);
	ft::pair<int&, int*> p4 = ft::make_pair(std::ref(n), a);
	n = 7;
	REQUIRE(p3.first == p4.first);
	REQUIRE(p3.second == p4.second);
}