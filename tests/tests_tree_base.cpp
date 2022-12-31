#include "tests.hpp"

TEST_CASE ("Test raso de TreeBase") {
	ft::TreeBase<int> t;

	REQUIRE(t.empty() == true);
	REQUIRE(t.size() == 0);

	t.insertUni(1);
	t.insertUni(2);
	t.insertUni(3);
	t.insertUni(4);
	t.insertUni(5);

	REQUIRE(t.empty() == false);
	REQUIRE(t.size() == 5);
	REQUIRE(t.isBalanced() == false);
	t.balance();
	REQUIRE(t.isBalanced() == true);
	t.clear();
	REQUIRE(t.empty() == true);
	REQUIRE(t.size() == 0);

}