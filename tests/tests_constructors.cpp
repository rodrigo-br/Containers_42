#include "tests.hpp"

TEST_CASE ("Passando array de String first e last no constructor") {
	print_line();
		std::string cavalinho[] = {"cavalinho", "na", "chuva", "ao", "vento"};
		ft::vector<std::string> v(std::begin(cavalinho), std::end(cavalinho));
		std::vector<std::string> v2(std::begin(cavalinho), std::end(cavalinho));

		simple_compare(v, v2);
}

TEST_CASE ("Passando array de int first e last no constructor") {
		int cavalinho[] = {1, 2, 3, 4, 5};
		ft::vector<int> v(std::begin(cavalinho), std::end(cavalinho));
		std::vector<int> v2(std::begin(cavalinho), std::end(cavalinho));

		simple_compare(v, v2);
}

TEST_CASE ("Passando <int> size 5 no constructor") {
		ft::vector<int> v(5);
		std::vector<int> v2(5);

		compare(v, v2);
}

TEST_CASE ("Passando int no constructor vazio") {
		ft::vector<int> v;
		std::vector<int> v2;

		compare(v, v2);
}
