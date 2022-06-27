NAME_VEC = test
NAME_VEC_STD = test_std
SRCS_VEC = test.cpp
SRCS_VEC_STD = test_std.cpp

all: $(NAME_VEC)

$(NAME_VEC): $(SRCS_VEC) $(SRCS_VEC_STD)
	@ clang++ -std=c++98 -Wall -Wextra -Werror $(SRCS_VEC) -o $(NAME_VEC)
	@ clang++ -std=c++98 -Wall -Wextra -Werror $(SRCS_VEC_STD) -o $(NAME_VEC_STD)
	@ clang++ -std=c++98 -Wall -Wextra -Werror comparator.cpp -o comparator

run:
	./test
	./test_std
	./comparator

clean:
	@ rm -f $(NAME_VEC)
	@ rm -f $(NAME_VEC_STD)
	@ rm -f comparator
	@ rm -f vec_output.txt
	@ rm -f vec_output_std.txt

re : clean all
