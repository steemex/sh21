FUNCTIONS = functions/*.c s21_string.h functions/*.h
GCC = gcc -Werror -Wall -Wextra -std=c11
CC = gcc -std=c11
GLFLAGS=--coverage
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LIB_NAME = s21_string.a
UNIT_TEST=-o unit_test
LIB=-lcheck
GCOV_TEST=-o gcov_test
ifeq ($(shell uname), Linux)
 LIB +=-lpthread -lrt -lsubunit -lm
endif


all: s21_string.a

s21_string.a:
	$(GCC) -c $(FUNCTIONS)
	make build_library
	rm -rf *.o rm -rf functions/*.gch *.gch

build_library:
	ar rcs s21_string.a *.o

clang:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i ${FUNCTIONS} s21_string_tests.c
	rm -rf .clang-format

test: ${LIB_NAME}
	${GCC} ${UNIT_TEST} ${wildcard *.c} ${LIB_NAME} ${LIB} 
	./unit_test
	rm ${LIB_NAME}
	rm unit_test
	rm -rf functions/*.gch *.gch

gcov_report: 
	${GCC} ${STD_FLAGS} ${GCOV_FLAGS} --coverage ${wildcard functions/*.c} ${GCOV_TEST} ${wildcard *.c}  ${LIB}
	./gcov_test
	lcov -t "stest" -o s21_test.info -c -d . -no-external
	genhtml -o report s21_test.info
	open ./report/index.html
	rm gcov_test
	rm -rf *.info *.gcno *.gcda gcov_report test *.a functions/*.gch *.gch


clean:
	rm -rf *.o *.gcno *.gcov *.gcda *.a *.info *.gch functions/*.gch gcov s21_string_tests

rebuild:
	make clean
	make
