#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "TreeBase.hpp"
#include "Tree.hpp"

typedef ft::TreeBase<int> Tree;
/*
	This main only aims to test the compilation with the version c++98
*/
int main(void)
{
	ft::vector<int> x;
	(void)x;
	Tree t;
	t.insertUni(10);
}