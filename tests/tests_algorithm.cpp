#include "tests.hpp"

bool mypredicate (int i, int j) {
  return (i==j);
}

TEST_CASE ("Testando equal") {
  int myints[] = {20, 40, 60, 80, 100};            //   myints: 20 40 60 80 100
  ft::vector<int>myvector(myints, myints + 5);     // myvector: 20 40 60 80 100

  // using default comparison:
  REQUIRE(ft::equal(myvector.begin(), myvector.end(), myints) == true);
  myvector[3]=81;                                 // myvector: 20 40 60 81 100

  // using predicate comparison:
  REQUIRE(std::equal(myvector.begin(), myvector.end(), myints, mypredicate) == false);
}