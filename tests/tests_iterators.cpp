#include "tests.hpp"

TEST_CASE("Testando iterator_traits category usando typeid") {
	typedef ft::iterator_traits<int*> traits;
	REQUIRE(typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag));
}

TEST_CASE("Testando random_access_iterator ") {
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	std::vector<int>::iterator it2 = v2.begin();
	for (ft::vector<int>::iterator it1 = v1.begin(); it1 != v1.end(); it1++) {
		REQUIRE(*it2 == *it1);
		it2++;
	}
	for (ft::vector<int>::iterator it1 = v1.end(); it1 != v1.begin();) {
		it2-=1;
		it1-=1;
		REQUIRE(*it2 == *it1);
	}
	ft::vector<int>::iterator it1 = v1.begin();
	REQUIRE(*it2 == *it1);
	REQUIRE(*(it2 + 1) == *(it1 + 1));
	REQUIRE(it2[1] == it1[1]);
	it2++;
	REQUIRE(*it2 > *it1);
}

TEST_CASE("Testando reverse_iterator do random_accesss") {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    ft::vector<int> v1(std::begin(array), std::end(array));
    std::vector<int> v2(std::begin(array), std::end(array));

    typedef ft::vector<int>::iterator iter_type;
    typedef std::vector<int>::iterator iter_type2;
                                                                                                                 
    iter_type from_mine = v1.begin();
    iter_type until_mine = v1.end();
    iter_type2 from_original = v2.begin();
    iter_type2 until_original = v2.end();
    ft::reverse_iterator<iter_type> rev_until_mine (from_mine);
    ft::reverse_iterator<iter_type> rev_from_mine (until_mine);
    std::reverse_iterator<iter_type2> rev_until_original (from_original);
    std::reverse_iterator<iter_type2> rev_from_original (until_original);
    while (rev_from_mine != rev_until_mine)
    {
        REQUIRE(*rev_from_original == *rev_from_mine);
        *rev_from_mine++;
        *rev_from_original++;
    }
}
