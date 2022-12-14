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
	std::vector<int> v2;
	v1.push_back(0);
	v2.push_back(0);
	v1.push_back(5);
	v2.push_back(5);
	v1.push_back(10);
	v2.push_back(10);
	v1.push_back(15);
	v2.push_back(15);
	v1.push_back(20);
	v2.push_back(20);
	simple_compare(v1, v2);
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

TEST_CASE("Teste Assign function modo fill") {
	std::vector<int> original;
	ft::vector<int> myvector;

	original.assign(7, 100); // 7 ints with a value of 100
	myvector.assign(7, 100);

	simple_compare(myvector, original);
}

TEST_CASE("Teste Assign function modo range usando array de int") {
	std::vector<int> original;
	ft::vector<int> myvector;

	int myints[] = {1776,7,4};
	original.assign(myints,myints + 3);	// assigning from array.
	myvector.assign(myints,myints + 3);

	simple_compare(myvector, original);
}

TEST_CASE("Teste Assign function modo range usando iteradores") {
	std::vector<int> original;
	std::vector<int> original_final;
	ft::vector<int> myvector;
	ft::vector<int> myvector_final;

	original.assign (7,100);	// 7 ints with a value of 100
	myvector.assign (7,100);
	std::vector<int>::iterator it_original;
	ft::vector<int>::iterator it_myvector;
	it_original = original.begin();
	it_myvector = myvector.begin();

	original_final.assign(it_original, it_original + 5);
	myvector_final.assign(it_myvector, it_myvector + 5);

	simple_compare(myvector_final, original_final);
}

TEST_CASE("Test Swap member function") {
	ft::vector<int> old_foo (3, 100);
	ft::vector<int> new_bar (3, 100);   // three ints with a value of 100
 	ft::vector<int> old_bar (5, 200);
	ft::vector<int> new_foo (5, 200);   // five ints with a value of 200

	old_foo.swap(old_bar);
	REQUIRE(old_foo.size() == 5);
	REQUIRE(old_bar.size() == 3);

	for (size_t i = 0; i < new_bar.size(); i++) {
		REQUIRE(new_bar[i] == old_bar[i]);
	}

	for (size_t i = 0; i < new_foo.size(); i++) {
		REQUIRE(new_foo[i] == old_foo[i]);
	}
}

TEST_CASE("Test Swap NON-member function") {
	ft::vector<int> old_foo (3, 100);
	ft::vector<int> new_bar (3, 100);   // three ints with a value of 100
 	ft::vector<int> old_bar (5, 200);
	ft::vector<int> new_foo (5, 200);   // five ints with a value of 200

	swap(old_bar, old_foo);
	REQUIRE(old_foo.size() == 5);
	REQUIRE(old_bar.size() == 3);

	for (size_t i = 0; i < new_bar.size(); i++) {
		REQUIRE(new_bar[i] == old_bar[i]);
	}

	for (size_t i = 0; i < new_foo.size(); i++) {
		REQUIRE(new_foo[i] == old_foo[i]);
	}
}

TEST_CASE("Test Insert pos value com int") {
	std::vector<int> original;
	ft::vector<int> myvector;

	original.insert(original.begin(), 1);
	myvector.insert(myvector.begin(), 1);

	compare(myvector, original);
}

TEST_CASE("Test Insert pos e value com string") {
	std::vector<std::string> original;
	ft::vector<std::string> myvector;

	original.insert(original.begin(), "cavalinho");
	myvector.insert(myvector.begin(), "cavalinho");

	compare(myvector, original);
}

TEST_CASE("Test Insert pos, count e value com int") {
	std::vector<int> original;
	ft::vector<int> myvector;

	original.insert(original.begin(), 5, 1);
	myvector.insert(myvector.begin(), 5, 1);

	compare(myvector, original);
}

TEST_CASE("Test Insert pos, count e value com int não vazio") {
	std::vector<int> original;
	ft::vector<int> myvector;

	original.push_back(1);
	original.push_back(2);
	myvector.push_back(1);
	myvector.push_back(2);
	original.insert(original.begin() + 1, 5, 1);
	myvector.insert(myvector.begin() + 1, 5, 1);

	compare(myvector, original);
}

TEST_CASE("Test Insert int com iteradores") {
	std::vector<int> x = {1, 2, 3, 4, 5};
	std::vector<int> original;
	ft::vector<int> myvector;
	
	original.insert(original.begin(), x.begin(), x.end());
	myvector.insert(myvector.begin(), x.begin(), x.end());

	compare(myvector, original);
}

TEST_CASE("Test Insert string com iteradores") {
	std::vector<std::string> x = {"cavalinho", "na", "chuva"};
	std::vector<std::string> original;
	ft::vector<std::string> myvector;
	
	original.insert(original.begin(), x.begin(), x.end());
	myvector.insert(myvector.begin(), x.begin(), x.end());

	compare(myvector, original);
}

TEST_CASE ("Test clear") {
	std::vector<int> original;
	ft::vector<int> myvector;

	original.push_back(1);
	original.push_back(2);
	original.push_back(3);
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);

	original.clear();
	myvector.clear();

	simple_compare(myvector, original);
}
