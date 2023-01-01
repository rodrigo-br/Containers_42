#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "Map.hpp"

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
	ft::TreeBase<int> tree;
	(void)tree;
	ft::Tree<std::string, Word> tab;
	(void)tab;
	ft::RBTree<std::string, Word> rbt;
	(void)rbt;
	ft::map<std::string, unsigned> map;
	map.insert(ft::make_pair("a", 1));
}
