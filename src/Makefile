FLAGS=-std=c++17 -Wall -Werror -Wextra
TESTFLAGS=-lgtest

ifeq ($(shell uname), Linux)
	FLAGS+=-lm -lstdc++
endif

all:
	g++ $(FLAGS) *.cc
	valgrind --leak-check=full ./a.out

s21_matrix_oop.a: clean
	g++ $(FLAGS) -c functions/*.cc
	ar rcs s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a
	rm *.o

clean:
	rm -rf ./a.out *.o *.a test.dSYM test

valgrind-test:
	valgrind --leak-check=full ./test

test: s21_matrix_oop.a
	g++ -g s21_matrix_oop.a tests/*.cc $(FLAGS) $(TESTFLAGS) -o test
	./test

tr:
	g++ $(FLAGS) functions/*.cc
	./a.out