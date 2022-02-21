#include <iostream>
#include <vector>

int main(void) {
	std::vector<int> vec;
	std::cout << vec.capacity() << std::endl;
	if (vec.begin() == vec.end())
		std::cout << "vec.begin() == vec.end()" << std::endl;
	return (0);
}
