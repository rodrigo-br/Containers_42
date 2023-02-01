#include "tests.hpp"

TEST_CASE ("Constructor MAP")
{
	ft::map<int, std::string> map;
	std::map<int, std::string> map2;
	REQUIRE(map._tree.size() == 0);
	REQUIRE(map.get_allocator() == map2.get_allocator());
}

// TEST_CASE ("RANGE construtor MAP")
// {
// 	ft::map<int, std::string> map;
// 	map.insert(ft::make_pair<int, std::string>(1, "one"));
// 	map.insert(ft::make_pair<int, std::string>(2, "two"));
// 	map.insert(ft::make_pair<int, std::string>(3, "tree"));

// 	ft::map<int, std::string> map2(map.begin(), map.end());
// }

TEST_CASE ("Insert MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map[3] = "tree";
	REQUIRE(map[1] == "one");
	REQUIRE(map[2] == "two");
	REQUIRE(map[3] == "tree");
}

TEST_CASE ("Empty MAP")
{
	ft::map<int, std::string> map;
	REQUIRE(map.empty() == true);
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	REQUIRE(map.empty() == false);
}

TEST_CASE ("Size MAP")
{
	ft::map<int, std::string> map;
	REQUIRE(map.size() == 0);
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	REQUIRE(map.size() == 1);
}

TEST_CASE ("Clear MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	map.clear();
	REQUIRE(map.size() == 0);
}

TEST_CASE ("Swap MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));

	ft::map<int, std::string> map2;
	map2.insert(ft::make_pair<int, std::string>(4, "four"));
	map2.insert(ft::make_pair<int, std::string>(5, "five"));
	map2.insert(ft::make_pair<int, std::string>(6, "six"));

	map.swap(map2);
	REQUIRE(map[4] == "four");
	REQUIRE(map[5] == "five");
	REQUIRE(map[6] == "six");
	REQUIRE(map2[1] == "one");
	REQUIRE(map2[2] == "two");
	REQUIRE(map2[3] == "tree");
}

TEST_CASE ("Begin and End MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));

	std::map<int, std::string> map2;
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));

	ft::map<int, std::string>::iterator it = map.begin();
	ft::map<int, std::string>::iterator ite = map.end();
	std::map<int, std::string>::iterator it2 = map2.begin();
	std::map<int, std::string>::iterator ite2 = map2.end();

	while (it != ite)
	{
		REQUIRE(it->first == it2->first);
		REQUIRE(it->second == it2->second);
		it++;
		it2++;
	}
}

// TEST_CASE ("Count MAP")
// {
// 	ft::map<int, std::string> map;
// 	map.insert(ft::make_pair<int, std::string>(1, "one"));
// 	REQUIRE(map.count(1) == 1);
// 	REQUIRE(map.count(2) == 0);
// }

// TEST_CASE ("Max_size MAP") // WORNG VALUE
// {
// 	ft::map<int, std::string> map;
// 	std::map<int, std::string> map2;
// 	REQUIRE(map.max_size() == map2.max_size());
// }


