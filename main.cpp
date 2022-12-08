#include "vector.hpp"

void print_line() {
	std::cout << std::string(42, '-') << std::endl;
}

template <typename T>
void printVector(const ft::vector<T>&vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << "\n";
	}

	print_line();
}

int main(void)
{
	ft::vector<std::string> vector;

	vector.push_back("cavalinho");
	vector.push_back("na");
	vector.push_back("chuva");

	printVector(vector);
}