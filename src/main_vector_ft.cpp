// #include "vector.hpp"
// #include "iterator_traits.hpp"
// #include "reverse_iterator.hpp"
// #include "algorithm.hpp"
// #include "type_traits.hpp"
// #include "rbtree.hpp"
// #include "map.hpp"
// #include <map>
// #include <vector>
// #include <string>
// #include <ostream>
// #include <sys/time.h>

// size_t	time_now(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec * 1000000 + time.tv_usec);
// }

// int main(void)
// {
// 	size_t start = time_now();
// 	ft::vector<int> v1;

// 	v1.push_back(1);
// 	v1.push_back(2);
// 	std::cout << v1.front() << std::endl;
// 	std::cout << v1.back() << std::endl;
// 	std::cout << *v1.begin() << std::endl;
// 	std::cout << *v1.end() << std::endl;
// 	std::cout << *v1.rbegin() << std::endl;
// 	std::cout << *v1.rend() << std::endl;
// 	std::cout << v1.size() << std::endl;
// 	std::cout << v1.max_size() << std::endl;
// 	std::cout << v1.capacity() << std::endl;
// 	v1.resize(10);
// 	std::cout << v1.capacity() << std::endl;
// 	std::cout << v1.empty() << std::endl;
// 	v1.reserve(15);
// 	std::cout << v1.capacity() << std::endl;
// 	std::cout << v1[0] << std::endl;
// 	std::cout << v1.at(1) << std::endl;
// 	v1.assign(v1.begin(), --v1.end());
// 	std::cout << v1[0] << std::endl;
// 	v1.pop_back();
// 	v1.insert(v1.begin(), 1);
// 	std::cout << v1.front() << std::endl;
// 	v1.erase(v1.begin());
// 	std::cout << v1.front() << std::endl;
// 	v1.clear();
// 	std::cout << v1.size() << std::endl;
// 	std::cout << time_now() - start << std::endl;
// }
