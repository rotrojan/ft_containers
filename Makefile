test: include/vector.hpp my_main.cpp
	clang++ -Wall -Wextra -Werror --std=c++98 -pedantic my_main.cpp -I include/ -o test

42_test: include/vector.hpp my_main.cpp
	clang++ -Wall -Wextra -Werror --std=c++98 -pedantic main.cpp -I include/ -o test

fclean:
	rm -rf test

re: fclean test

.PHONY: clean re
