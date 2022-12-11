#include "tests.hpp"

TEST_CASE ("Tests resize com parâmetro menor que size atual") {
	int array[] {1, 2, 3, 4};
	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	v1.resize(2);
	v2.resize(2);

	compare(v1, v2);
}

TEST_CASE ("Tests resize com parâmetro menor que size atual definindo val") {
	int array[] {1, 2, 3, 4};
	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	v1.resize(2, 10);
	v2.resize(2, 10);

	compare(v1, v2);
}

TEST_CASE ("Tests resize com parâmetro igual ao size atual") {
	int array[] {1, 2, 3, 4};
	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	v1.resize(4);
	v2.resize(4);

	compare(v1, v2);
}

TEST_CASE ("Tests resize com parâmetro maior ao size atual com val default") {
	int array[] {1, 2, 3, 4};
	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	v1.resize(10);
	v2.resize(10);

	compare(v1, v2);
}

TEST_CASE ("Tests resize com parâmetro maior ao size atual com val definido") {
	int array[] {1, 2, 3, 4};
	ft::vector<int> v1(std::begin(array), std::end(array));
	std::vector<int> v2(std::begin(array), std::end(array));

	v1.resize(10, 5);
	v2.resize(10, 5);

	compare(v1, v2);
}