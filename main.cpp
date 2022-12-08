#include "vector.hpp"

int main(void)
{
	ft::vector<std::string> vector;

	vector.push_back("cavalinho");
	vector.push_back("na");
	vector.push_back("chuva");

	for (size_t i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << std::endl;
	}
}