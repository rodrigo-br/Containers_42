#include "tests.hpp"

class A {};
 
enum E : int {};
 
template <class T>
T f(T i)
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    return i;
}
 
TEST_CASE ("Test is_integral")
{ 
    REQUIRE(ft::is_integral<A>::value == false);
    REQUIRE(ft::is_integral<E>::value == false);
    REQUIRE(ft::is_integral<float>::value == false);
    REQUIRE(ft::is_integral<int*>::value == false);
    REQUIRE(ft::is_integral<int>::value == true);
    REQUIRE(ft::is_integral<const int>::value == true);
    REQUIRE(ft::is_integral<bool>::value == true);
    REQUIRE(ft::is_integral<char>::value == true);
    REQUIRE( f(123) == 123);
}