#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "TreeBase.hpp"
#include "Tree.hpp"
#include "RBTree.hpp"

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
	ft::vector<int> x;
	(void)x;
	ft::TreeBase<int> t;
	(void)t;
	ft::Tree<std::string, Word> tab;
	(void)tab;
	ft::RBTree<std::string, Word> rbt;
	rbt.insertUni(Word("a"));
	rbt.printOn(std::cout);
	std::cout << std::string(42, '-') << std::endl;
	rbt.insertUni(Word("b"));
	rbt.printOn(std::cout);
	std::cout << std::string(42, '-') << std::endl;
	rbt.insertUni(Word("c"));
	rbt.printOn(std::cout);
	std::cout << std::string(42, '-') << std::endl;
	rbt.insertUni(Word("e", 1));
	rbt.printOn(std::cout);
	std::cout << std::string(42, '-') << std::endl;
	rbt.insertUni(Word("d", 5));
	rbt.printOn(std::cout);
	std::cout << std::string(42, '-') << std::endl;
	rbt.insertUni(Word("0"));
	rbt.printOn(std::cout);
	std::cout << std::string(42, '-') << std::endl;
	rbt.insertUni(Word("A"));
	rbt.printOn(std::cout);
	std::cout << std::string(42, '-') << std::endl;
	std::cout << rbt.isBalanced() << std::endl;
}
