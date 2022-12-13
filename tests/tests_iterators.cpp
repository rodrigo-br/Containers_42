#include "tests.hpp"

TEST_CASE("Testando iterator_traits category usando typeid") {
	typedef ft::iterator_traits<int*> traits;
	REQUIRE(typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag));
}

TEST_CASE("Não faço ideia do que isso aqui tá testando, mano") {
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	REQUIRE(v2.begin() == v1.begin());
}