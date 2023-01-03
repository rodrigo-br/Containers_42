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
	(void)map;
	rbt.insertUni(Word("a", 1));
	rbt.insertUni(Word("b", 2));
	rbt.insertUni(Word("c", 3));
	rbt.insertUni(Word("d", 4));
	rbt.insertUni(Word("e", 5));
	rbt.insertUni(Word("f", 6));
	rbt.insertUni(Word("g", 7));
	rbt.insertUni(Word("h", 8));
	rbt.insertUni(Word("i", 9));
	rbt.insertUni(Word("j", 10));
	rbt.insertUni(Word("k", 11));
	rbt.insertUni(Word("A", 0));
	rbt.insertUni(Word(" ", 0));
	rbt.insertUni(Word("b", 0));
	rbt.printOn(std::cout);
}
