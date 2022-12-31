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
	operator const std::string &() const { return word; };
};

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
}