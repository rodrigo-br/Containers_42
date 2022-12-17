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

TEST_CASE("Teste Push back com _size < _capacity") {
	ft::vector<int> v1;
	v1.reserve(5);
	v1.push_back(0);
	v1.push_back(5);
	v1.push_back(10);
	v1.push_back(15);
	v1.push_back(20);
	for (int i = 0; i < v1.size(); i++) {
		REQUIRE(i * 5 == v1[i]);
	}
}

TEST_CASE("Teste Push back com _capacity 0 e _size + 1 > _capacity") {
	ft::vector<int> v1;
	v1.push_back(0);
	v1.push_back(5);
	v1.push_back(10);
	v1.push_back(15);
	v1.push_back(20);
	for (int i = 0; i < v1.size(); i++) {
		REQUIRE(i * 5 == v1[i]);
	}
}

TEST_CASE("Teste Pop") {
	ft::vector<int> v1;
	v1.push_back(1);
	REQUIRE(v1[0] == 1);
	REQUIRE(v1.size() == 1);
	v1.pop_back();
	REQUIRE(v1.size() == 0);
	v1.push_back(2);
	REQUIRE(v1[0] == 2);
}
