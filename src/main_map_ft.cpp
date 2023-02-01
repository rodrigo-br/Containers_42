// #include "vector.hpp"
// #include "iterator_traits.hpp"
// #include "reverse_iterator.hpp"
// #include "algorithm.hpp"
// #include "type_traits.hpp"
// #include "rbtree.hpp"
// #include "map.hpp"
// #include "utility.hpp"
// #include <utility>
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
// 	ft::map<int, std::string> map;
// 	int a = 1;
// 	int b = 2;
// 	std::string c = "one";
// 	std::string d = "two";
// 	map.insert(ft::make_pair<int, std::string>(a, c));
// 	map.insert(ft::make_pair<int, std::string>(b, d));
// 	std::cout << map.begin()->first << std::endl;
// 	std::cout << map.begin()->second << std::endl;
// 	std::cout << map.rbegin()->first << std::endl;
// 	std::cout << map.rbegin()->second << std::endl;
// 	std::cout << map.empty() << std::endl;
// 	std::cout << map.size() << std::endl;
// 	std::cout << map[1] << std::endl;
// 	std::cout << map.at(2) << std::endl;
// 	map.erase(2);
// 	std::cout << map.size() << std::endl;
// 	map[2] = "two";
// 	std::cout << map.size() << std::endl;
// 	std::cout << map.find(2)->first << std::endl;
// 	std::cout << map.find(2)->second << std::endl;
// 	std::cout << map.count(2) << std::endl;
// 	std::cout << map.count(3) << std::endl;
// 	std::cout << map.lower_bound(2)->first << std::endl;
// 	std::cout << map.lower_bound(2)->second << std::endl;
// 	std::cout << map.equal_range(2).first->second << std::endl;
// 	std::cout << time_now() - start << std::endl;
// }