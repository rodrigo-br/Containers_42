#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "TreeBase.hpp"
#include "Tree.hpp"

/*
	This main only aims to test the compilation with the version c++98
*/
int main(void)
{
	ft::vector<int> x;
	(void)x;
	ft::TreeBase<int> t;
	(void)t;
}