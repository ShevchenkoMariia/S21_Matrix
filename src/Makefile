CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
CHECK_FLAGS = -lcheck -pthread -lm -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage 
LDFLAGS = -L. s21_matrix.a
TESTS = $(wildcard tests/test*.c)
SRC = $(wildcard s21*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

all: gcov_report clean

s21_matrix.a: clean $(OBJ) 
	@ar rc $@ $(OBJ)
	@ranlib $@
	@rm *.o

%.o : %.c
	@$(CC) $(CFLAGS) -c $< 

test: clean s21_matrix.a
	@$(CC) $(CFLAGS) $(SRC) $(TESTS) $(LDFLAGS) $(CHECK_FLAGS) $(GCOV_FLAGS)
	@./a.out

gcov_report: clean test
	@lcov -c -d . -o coverage.info
	@genhtml coverage.info -o gcov_report
	@open gcov_report/index.html

clean:
	@rm -rf *.o *.gcda *.gcno gcov_report s21_matrix.a coverage.info a.out

check_style:
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.c *.h tests/*.c tests/*.h
	@rm .clang-format

style:
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.c *.h tests/*.c tests/*.h
	@rm .clang-format

g_style:
	@clang-format --style=Google -n *.c *.h tests/*.c tests/*.h

valgrind: clean s21_matrix.a
	$(CC) $(CFLAGS) $(SRC) $(TESTS) $(LDFLAGS) $(CHECK_FLAGS)
	 valgrind --tool=memcheck --leak-check=yes ./a.out
#valgrind: clean s21_matrix.a
#	$(CC) $(SRC) tests/test_determinant.c tests/testing.c tests/test_helper_fn.c $(LDFLAGS) $(CHECK_FLAGS)
#	valgrind --tool=memcheck --leak-check=yes ./a.out
