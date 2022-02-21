#include <iostream>
#include <vector>
#include "include/vector.hpp"
#define SIZE 1
#define VALUE 42

int main() {
	ft::vector<int> ftvec;
	std::vector<int> stdvec;

	for (int i = 0; i < 100; ++i) {
		ftvec.insert(ftvec.begin(), SIZE, VALUE);
		stdvec.insert(stdvec.begin(), SIZE, VALUE);
		// if (stdvec.capacity() != ftvec.capacity()) {
			std::cout << " ft_vec = " << ftvec.capacity() << std::endl;
			std::cout << "std_vec = " << stdvec.capacity() << std::endl;
			std::cout << "i = " << i << std::endl;
		// }
	}
	// for (int i = 0; i < 100; ++i) {
		// ftvec.pop_back();
		// stdvec.pop_back();
		// if (stdvec[stdvec.size()] != ftvec[stdvec.size()]) {
			// std::cout << " ft_vec = " << ftvec[ftvec.size()] << std::endl;
			// std::cout << "std_vec = " << stdvec[stdvec.size()] << std::endl;
			// std::cout << "i = " << i << std::endl;
		// }
	// }

	return 0;
}
