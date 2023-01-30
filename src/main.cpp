#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "rbtree.hpp"
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
	ft::RBTree<int, ft::pair<int, std::string> > tree;
	tree.insertUni(ft::make_pair(1, "one"));
}
