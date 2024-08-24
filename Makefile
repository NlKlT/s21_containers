CC = gcc
CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra

EXECUTABLE = test

SRC_LIST_TEST = ./tests/list_tests.cpp
SRC_STACK_TEST = ./tests/stack_tests.cpp
SRC_QUEUE_TEST = ./tests/queue_tests.cpp
SRC_MAP_TEST = ./tests/map_tests.cpp
SRC_SET_TEST = ./tests/set_tests.cpp
SRC_MULTISET_TEST = ./tests/multiset_tests.cpp
SRC_VECTOR_TEST = ./tests/vector_tests.cpp
SRC_ARRAY_TEST = ./tests/array_tests.cpp

SOURCE = $(SRC_LIST_TEST) $(SRC_STACK_TEST) $(SRC_QUEUE_TEST) $(SRC_MAP_TEST) $(SRC_SET_TEST) $(SRC_MULTISET_TEST) $(SRC_VECTOR_TEST) $(SRC_ARRAY_TEST)

UNAME = $(shell uname)

OPEN_REPORT :=
LEAKS :=

ifeq ($(UNAME), Linux)
OPEN_REPORT += xdg-open
LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN_REPORT += open
LEAKS += leaks -atExit --
endif

all: clean test

clean:
	@rm -rf $(EXECUTABLE)
	@rm -rf a.out
	@rm -rf $(OBJ_LIST_TEST)
	@rm -rf $(OBJ_STACK_TEST)
	@rm -rf *.gcno *.gcda report
	@rm -rf tests.info

test:
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

gcov_report: clean
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) --coverage
	@./$(EXECUTABLE)
	mkdir report
	gcovr -r . --html --html-details -o ./report/coverage_report.html
	rm -f *.gcda *.gcno
	$(OPEN_REPORT) ./report/coverage_report.html

style:
	clang-format -n --style=google s21_containers.h
	clang-format -n --style=google s21_containersplus.h
	clang-format -n --style=google list/*.h
	clang-format -n --style=google stack/*.h
	clang-format -n --style=google queue/*.h
	clang-format -n --style=google tree/*.h
	clang-format -n --style=google map/*.h
	clang-format -n --style=google set/*.h
	clang-format -n --style=google multiset/*.h
	clang-format -n --style=google array/*.h
	clang-format -n --style=google vector/*.h
	clang-format -n --style=google tests/*.cc

clang_format:
	clang-format -i --style=google s21_containers.h
	clang-format -i --style=google s21_containersplus.h
	clang-format -i --style=google list/*.h
	clang-format -i --style=google stack/*.h
	clang-format -i --style=google queue/*.h
	clang-format -i --style=google tree/*.h
	clang-format -i --style=google map/*.h
	clang-format -i --style=google set/*.h
	clang-format -i --style=google multiset/*.h
	clang-format -i --style=google array/*.h
	clang-format -i --style=google vector/*.h
	clang-format -i --style=google tests/*.cc

leaks_check: test
	@$(LEAKS) ./$(EXECUTABLE)


fsanitize_check:
	@$(CC) -fsanitize=address $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_list:
	@$(CC) $(CFLAGS) $(SRC_LIST_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_stack:
	@$(CC) $(CFLAGS) $(SRC_STACK_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_queue:
	@$(CC) $(CFLAGS) $(SRC_QUEUE_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_map:
	@$(CC) $(CFLAGS) $(SRC_MAP_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_set:
	@$(CC) $(CFLAGS) $(SRC_SET_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_multiset:
	@$(CC) $(CFLAGS) $(SRC_MULTISET_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_vector:
	@$(CC) $(CFLAGS) $(SRC_VECTOR_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

test_array:
	@$(CC) $(CFLAGS) $(SRC_ARRAY_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

run:
	./$(EXECUTABLE)

.PHONY: all clean test gcov_report style clang_format leaks_check run