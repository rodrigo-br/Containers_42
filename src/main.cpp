#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "rbtree.hpp"
#include "map.hpp"
#include <map>
#include <string>
#include <ostream>

struct Word {
	std::string word;
	unsigned count;
	Word(const std::string &w) : word(w), count(0) {};
	Word(const std::string &w, unsigned c) : word(w), count(c) {};
	operator const std::string &() const { return word; };
};

std::ostream &operator<<(std::ostream &os, const Word &w) {
	return os << w.word << " " << w.count;
}

/*
	This main only aims to test the compilation with the version c++98
*/
int main(void)
{
	ft::vector<int> vec;
	(void)vec;
	ft::map<int, std::string> map;
	(void)map;
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(2, "two"));
	map[3] = "tree";
	map._tree.printOn(std::cout);

	std::cout << map[3] << std::endl;
	map.clear();
}
