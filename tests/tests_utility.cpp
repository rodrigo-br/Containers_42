#include "tests.hpp"

TEST_CASE("Testando Pair e Make Pair") {
	int n = 1;
	int a[5] = {1, 2, 3, 4, 5};
 
    // build a pair from two ints
	auto p1 = std::make_pair(n, a[1]);
	ft::pair<int, int> p2 = ft::make_pair(n, a[1]);
	REQUIRE(p1.first == p2.first);
	REQUIRE(p1.second == p2.second);
}