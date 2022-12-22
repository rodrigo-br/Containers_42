#include "tests.hpp"

TEST_CASE ("Testando operator= com vector vazio") {
	ft::vector<int> x(5);
	ft::vector<int> y;

	y = x;
	for (size_t i = 0; i < x.size(); i++) {
		REQUIRE(y[i] == x[i]);
	}
}

TEST_CASE ("Testando operator= com vector(5)") {
	int cavalinho[] = {1, 2, 3, 4, 5};
	ft::vector<int> x(std::begin(cavalinho), std::end(cavalinho));
	ft::vector<int> y(5);

	y = x;
	for (size_t i = 0; i < x.size(); i++) {
		REQUIRE(y[i] == x[i]);
	}
}

TEST_CASE("Test operator== com vector int vazio") {
	ft::vector<int> x;
	ft::vector<int> y;

	REQUIRE((x == y) == true);
}

TEST_CASE("Test operator== com vector int iguais") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(5, 100);

	REQUIRE((x == y) == true);
}

TEST_CASE("Test operator== com vector int diferentes") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(5, 80);

	REQUIRE((x == y) == false);
}

TEST_CASE("Test operator!= com vector int vazio") {
	ft::vector<int> x;
	ft::vector<int> y;

	REQUIRE((x != y) == false);
}

TEST_CASE("Test operator!= com vector int iguais") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(5, 100);

	REQUIRE((x != y) == false);
}

TEST_CASE("Test operator!= com vector int diferentes") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(5, 80);

	REQUIRE((x != y) == true);
}

TEST_CASE("Test operator< com vector int") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(4, 100);
	std::vector<int> x2(5, 100);
	std::vector<int> y2(4, 100);

	REQUIRE((x < y) == (x2 < y2));

	ft::vector<int> z(4, 100);
	std::vector<int> z2(4, 100);

	REQUIRE((y < z) == (y2 < z2));

	ft::vector<int> w(4, 100);
	std::vector<int> w2(4, 100);

	w.pop_back();
	w2.pop_back();
	w.push_back(101);
	w2.push_back(101);

	REQUIRE((z < w) == (z2 < w2));
}

TEST_CASE("Test operator> com vector int") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(4, 100);
	std::vector<int> x2(5, 100);
	std::vector<int> y2(4, 100);

	REQUIRE((x > y) == (x2 > y2));

	ft::vector<int> z(4, 100);
	std::vector<int> z2(4, 100);

	REQUIRE((y > z) == (y2 > z2));

	ft::vector<int> w(4, 100);
	std::vector<int> w2(4, 100);

	w.pop_back();
	w2.pop_back();
	w.push_back(101);
	w2.push_back(101);

	REQUIRE((z > w) == (z2 > w2));
}

TEST_CASE("Test operator>= com vector int") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(4, 100);
	std::vector<int> x2(5, 100);
	std::vector<int> y2(4, 100);

	REQUIRE((x >= y) == (x2 >= y2));

	ft::vector<int> z(4, 100);
	std::vector<int> z2(4, 100);

	REQUIRE((y >= z) == (y2 >= z2));

	ft::vector<int> w(4, 100);
	std::vector<int> w2(4, 100);

	w.pop_back();
	w2.pop_back();
	w.push_back(101);
	w2.push_back(101);

	REQUIRE((z >= w) == (z2 >= w2));
}

TEST_CASE("Test operator<= com vector int") {
	ft::vector<int> x(5, 100);
	ft::vector<int> y(4, 100);
	std::vector<int> x2(5, 100);
	std::vector<int> y2(4, 100);

	REQUIRE((x <= y) == (x2 <= y2));

	ft::vector<int> z(4, 100);
	std::vector<int> z2(4, 100);

	REQUIRE((y <= z) == (y2 <= z2));

	ft::vector<int> w(4, 100);
	std::vector<int> w2(4, 100);

	w.pop_back();
	w2.pop_back();
	w.push_back(101);
	w2.push_back(101);

	REQUIRE((z <= w) == (z2 <= w2));
}

