test: vector.hpp my_main.cpp
	clang++ -Wall -Wextra -Werror --std=c++98 -pedantic main.cpp -I. -o test

fclean:
	rm -rf test

re: fclean test

.PHONY: clean re
