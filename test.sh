#! /bin/bash
make fclean
make CXXFLAGS="-DSTD -Wall -Wextra -Werror -std=c++98"
./ft_containers_test > theirs
make re
./ft_containers_test > mine
diff mine theirs
