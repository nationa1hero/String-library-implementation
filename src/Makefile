.PHONY: all clean test s21_string.a check rebuild open gcov_report leaks
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -std=c11
LFLAGS	= -fprofile-arcs -ftest-coverage
LIBS    = -lcheck
LINUX   = -lpthread -lsubunit -lrt -lm
OS		= $(shell uname -s)

all: s21_string.a test

s21_string.a: s21_string.o
	ar rc s21_string.a s21_string.o
	ranlib s21_string.a
	rm -rf s21_string.o

s21_string.o:
	$(CC) -c s21_string.c

test: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) $(FLAGS) unit_testing.c s21_string.a -o darwin_tests $(LIBS)
	./darwin_tests
else
	$(CC) $(FLAGS) unit_testing.c s21_string.a -o linux_tests $(LIBS) $(LINUX)
	./linux_tests
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) unit_testing.c s21_string.c -o darwin_tests $(LIBS)
	./darwin_tests
	lcov -t "darwin_tests" -o darwin.info -c -d .
	genhtml -o darwin_report darwin.info
else
	$(CC) $(CFLAGS) $(LFLAGS) unit_testing.c s21_string.c -o linux_tests $(LIBS) $(LINUX)
	./linux_tests
	lcov -t "linux_tests" -o linux.info -c -d .
	genhtml -o linux_report linux.info
endif

open:
ifeq ($(OS), Darwin)
	open darwin_report/index.html
else
	open linux_report/index.html
endif

rebuild: clean all

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	make test
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) unit_testing.c s21_string.c -o darwin_tests $(LIBS)
	CK_FORK=no leaks --atExit -- ./darwin_tests
else
	$(CC) $(CFLAGS) unit_testing.c s21_string.c -o linux_tests $(LIBS) $(LINUX)
	valgrind ./linux_tests --leaks-check=full
endif
	make clean

leaks:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) unit_testing.c s21_string.c -o darwin_tests $(LIBS)
	CK_FORK=no leaks --atExit -- ./darwin_tests
else
	$(CC) $(CFLAGS) unit_testing.c s21_string.c -o linux_tests $(LIBS) $(LINUX)
	valgrind ./linux_tests --leaks-check=full
endif

clean:
ifeq ($(OS), Darwin)
	rm -rf *.gc* *.o *.a *.info darwin_tests
	rm -rf darwin_report
else
	rm -rf *.gc* *.o *.a *.info linux_tests
	rm -rf linux_report
endif
