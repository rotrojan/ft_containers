#! /bin/bash
c++ insert.cpp -I include -DUSING_STD -I containers_test/srcs/vector && ./a.out > theirs
c++ insert.cpp -I include -I containers_test/srcs/vector && ./a.out > mine
diff mine theirs
