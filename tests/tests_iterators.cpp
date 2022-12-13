#include "tests.hpp"

// TEST_CASE("Testando iterator_traits category usando typeid") {
// 	typedef ft::iterator_traits<int*> traits;
// 	REQUIRE(typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag));
// }

// TEST_CASE("Não faço ideia do que isso aqui tá testando, mano") {
// 	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// 	ft::vector<int> myvector(std::begin(array), std::end(array));

// 	typedef std::vector<int>::iterator iter_type;

// 	iter_type from (myvector.begin());

// 	iter_type until (myvector.end());

// 	std::reverse_iterator<iter_type> rev_until (from);

// 	std::reverse_iterator<iter_type> rev_from (until);

// 	std::cout << "myvector:";
// 	while (rev_from != rev_until)
// 		std::cout << ' ' << *rev_from++;
// 	std::cout << std::endl;
// }