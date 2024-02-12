CC = gcc
CFLAGS = -g -Wall -std=c11

all: t9_tests t9_tests_buggy t9_demo

test: t9_tests
	./t9_tests

test-buggy: t9_tests_buggy
	./t9_tests_buggy

t9_tests: t9_tests.o t9_lib.o
	$(CC) $(CFLAGS) -o $@ $^

t9_tests_buggy: t9_tests.o t9_lib_buggy.o
	$(CC) $(CFLAGS) -o $@ $^

t9_demo: t9_demo.o t9_lib.o
	$(CC) $(CFLAGS) -o $@ $^

t9_tests.o: t9_tests.c t9_lib.h safe_assert.h
	$(CC) $(CFLAGS) -o $@ -c $<

t9_demo.o: t9_demo.c t9_lib.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f t9_demo.o t9_tests.o t9_tests t9_tests_buggy t9_demo