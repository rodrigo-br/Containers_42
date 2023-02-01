#include "tests.hpp"

TEST_CASE ("Constructor MAP")
{
	ft::map<int, std::string> map;
	std::map<int, std::string> map2;
	REQUIRE(map._tree.size() == 0);
	REQUIRE(map.get_allocator() == map2.get_allocator());
}

TEST_CASE ("Range construtor MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));

	ft::map<int, std::string> map2(map.begin(), map.end());
	REQUIRE(map[1] == map2[1]);
	REQUIRE(map[2] == map2[2]);
	REQUIRE(map[3] == map2[3]);
}

TEST_CASE ("Copy construtor MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));

	ft::map<int, std::string> map2(map);
	REQUIRE(map[1] == map2[1]);
	REQUIRE(map[2] == map2[2]);
	REQUIRE(map[3] == map2[3]);
}

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

TEST_CASE ("Key_comp MAP")
{
	ft::map<int, std::string>map;
	std::map<int, std::string>map2;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));
	auto kc = map.key_comp();
	auto kc2 = map2.key_comp();

	REQUIRE(kc(1, 2) == kc2(1, 2));
	REQUIRE(kc(2, 1) == kc2(2, 1));
	REQUIRE(kc(1, 1) == kc2(1, 1));
}

TEST_CASE ("Value_comp MAP")
{
	ft::map<int, std::string>map;
	std::map<int, std::string>map2;
	auto vc = map.value_comp();
	auto vc2 = map2.value_comp();

	REQUIRE(vc(
				ft::make_pair<int, std::string>(1, "one"),
				ft::make_pair<int, std::string>(2, "two")
				) 
			==
			vc2(
				std::make_pair<int, std::string>(1, "one"),
				std::make_pair<int, std::string>(2, "two")
				)
			);
	REQUIRE(vc(
				ft::make_pair<int, std::string>(2, "two"),
				ft::make_pair<int, std::string>(1, "one")
				) 
			==
			vc2(
				std::make_pair<int, std::string>(2, "two"),
				std::make_pair<int, std::string>(1, "one")
				)
			);
}

TEST_CASE ("Operators overload MAP")
{
	std::map<int, char> alice;
	alice.insert(std::make_pair<int, char>(1, 'a'));
	alice.insert(std::make_pair<int, char>(2, 'b'));
    std::map<int, char> bob;
	bob.insert(std::make_pair<int, char>(7, 'Z'));
	bob.insert(std::make_pair<int, char>(8, 'Y'));
	bob.insert(std::make_pair<int, char>(9, 'X'));
	std::map<int, char> eve;
	eve.insert(std::make_pair<int, char>(1, 'a'));
	eve.insert(std::make_pair<int, char>(2, 'b'));
	ft::map<int, char> alice2;
	alice2.insert(ft::make_pair<int, char>(1, 'a'));
	alice2.insert(ft::make_pair<int, char>(2, 'b'));
	ft::map<int, char> bob2;
	bob2.insert(ft::make_pair<int, char>(7, 'Z'));
	bob2.insert(ft::make_pair<int, char>(8, 'Y'));
	bob2.insert(ft::make_pair<int, char>(9, 'X'));
	ft::map<int, char> eve2;
	eve2.insert(ft::make_pair<int, char>(1, 'a'));
	eve2.insert(ft::make_pair<int, char>(2, 'b'));
 
    // Compare non equal containers
    REQUIRE((alice == bob) == (alice2 == bob2));
    REQUIRE((alice != bob) == (alice2 != bob2));
    REQUIRE((alice < bob) == (alice2 < bob2));
    REQUIRE((alice <= bob) == (alice2 <= bob2));
    REQUIRE((alice > bob) == (alice2 > bob2));
    REQUIRE((alice >= bob) == (alice2 >= bob2));
 
	// Compare equal containers
    REQUIRE((alice == eve) == (alice2 == eve2));
    REQUIRE((alice != eve) == (alice2 != eve2));
    REQUIRE((alice < eve) == (alice2 < eve2));
    REQUIRE((alice <= eve) == (alice2 <= eve2));
    REQUIRE((alice > eve) == (alice2 > eve2));
    REQUIRE((alice >= eve) == (alice2 >= eve2));
}

TEST_CASE ("Find MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	std::map<int, std::string> map2;
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));
	ft::map<int, std::string>::iterator it = map.find(2);
	std::map<int, std::string>::iterator it2 = map2.find(2);
	REQUIRE(it->first == it2->first);
	REQUIRE(it->second == it2->second);
}

TEST_CASE ("At MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	std::map<int, std::string> map2;
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));
	REQUIRE(map.at(1) == map2.at(1));
	REQUIRE(map.at(2) == map2.at(2));
	REQUIRE(map.at(3) == map2.at(3));
}

TEST_CASE ("Erase (iterator) MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	std::map<int, std::string> map2;
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));
	REQUIRE(map.size() == map2.size());
	map.erase(map.begin());
	map2.erase(map2.begin());
	REQUIRE(map.size() == map2.size());
	REQUIRE(map.at(2) == map2.at(2));
	REQUIRE(map.at(3) == map2.at(3));
}

TEST_CASE ("Erase (first, last) MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	std::map<int, std::string> map2;
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));
	REQUIRE(map.size() == map2.size());
	map.erase(map.begin(), ++map.begin());
	map2.erase(map2.begin(), ++map2.begin());
	REQUIRE(map.size() == map2.size());
}

TEST_CASE ("Equal_range MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	std::map<int, std::string> map2;
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));
	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> pair = map.equal_range(2);
	std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> pair2 = map2.equal_range(2);
	REQUIRE(pair.first->first == pair2.first->first);
	REQUIRE(pair.first->second == pair2.first->second);
	REQUIRE(pair.second->first == pair2.second->first);
	REQUIRE(pair.second->second == pair2.second->second);
}

TEST_CASE ("Non-member Swap MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	ft::map<int, std::string> map2;
	map2.insert(ft::make_pair<int, std::string>(4, "four"));
	map2.insert(ft::make_pair<int, std::string>(5, "five"));
	std::map<int, std::string> map3;
	map3.insert(std::make_pair<int, std::string>(4, "four"));
	map3.insert(std::make_pair<int, std::string>(5, "five"));

	REQUIRE(map2[4] == map3[4]);
	REQUIRE(map2[5] == map3[5]);
	ft::swap(map, map2);
	REQUIRE(map[1] == map3[1]);
	REQUIRE(map[2] == map3[2]);
	
}

TEST_CASE ("Erase (key) MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map.insert(ft::make_pair<int, std::string>(3, "tree"));
	std::map<int, std::string> map2;
	map2.insert(std::make_pair<int, std::string>(1, "one"));
	map2.insert(std::make_pair<int, std::string>(2, "two"));
	map2.insert(std::make_pair<int, std::string>(3, "tree"));
	REQUIRE(map.size() == map2.size());
	map.erase(2);
	map2.erase(2);
	REQUIRE(map.size() == map2.size());
	REQUIRE(map.at(1) == map2.at(1));
	REQUIRE(map.at(3) == map2.at(3));
}

TEST_CASE ("Count MAP")
{
	ft::map<int, std::string> map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	REQUIRE(map.count(1) == 1);
	REQUIRE(map.count(2) == 0);
}

// TEST_CASE ("Max_size MAP") // WORNG VALUE
// {
// 	ft::map<int, std::string> map;
// 	std::map<int, std::string> map2;
// 	REQUIRE(map.max_size() == map2.max_size());
// }


