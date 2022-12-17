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

TEST_CASE("Teste Pop back function") {
	ft::vector<int> v1;
	v1.push_back(1);
	REQUIRE(v1[0] == 1);
	REQUIRE(v1.size() == 1);
	v1.pop_back();
	REQUIRE(v1.size() == 0);
	v1.push_back(2);
	REQUIRE(v1[0] == 2);
}

TEST_CASE("Teste erase position") {
	std::vector<int> original;
	ft::vector<int> myvector;

  // set some values (from 1 to 5)
	for (int i = 1; i <= 5; i++) original.push_back(i);
	for (int i = 1; i <= 5; i++) myvector.push_back(i);

	// erase the 6th element
	original.erase(original.begin() + 3);
	myvector.erase(myvector.begin() + 3);

	for (unsigned i = 0; i < original.size(); ++i)
		REQUIRE(original[i] == myvector[i]);
}

TEST_CASE("Teste erase range") {
	std::vector<int> original;
	ft::vector<int> myvector;

  	// set some values (from 1 to 5)
	for (int i = 1; i <= 5; i++) original.push_back(i);
	for (int i = 1; i <= 5; i++) myvector.push_back(i);

	 // erase the first 3 elements:
	 original.erase(original.begin() ,original.begin() + 3);
	 myvector.erase(myvector.begin() ,myvector.begin() + 3);

	for (unsigned i = 0; i < original.size(); ++i)
		REQUIRE(original[i] == myvector[i]);
}

TEST_CASE("Teste Assign function") {
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;

	first.assign (7,100);	 // 7 ints with a value of 100

	std::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);	 // assigning from array.

	REQUIRE(first.size() == 7);
	REQUIRE(second.size() == 5);
	REQUIRE(third.size() == 3);
}

