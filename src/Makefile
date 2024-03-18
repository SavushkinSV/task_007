CFLAGS=-Werror -Wextra -Wall 
CC=gcc
FSAN=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector

all: change_separator binary_div

change_separator: change_separator.c
	$(CC) $(CFLAGS) change_separator.c -o ../bin/change_separator

binary_div: binary_div.c
	$(CC) $(CFLAGS) binary_div.c -o ../bin/binary_div -lm

clean:
	rm -rf *.o *.out

check:
	clang-format -style='{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}' -n *.c
	# clang-format -style='{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}' -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	# valgrind --tool=memcheck --leak-check=yes ../bin/change_separator