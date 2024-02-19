# Variable definitions
CC = gcc
CFLAGS = -g -Wall -std=c11

# Target 1: t9_lib.o
t9_lib.o: t9_lib.c t9_priv.h
	$(CC) $(CFLAGS) -o $@ -c t9_lib.c

# target 2: t9_demo.o
t9_demo.o: t9_demo.c t9_priv.h
	$(CC) $(CFLAGS) -o $@ -c t9_demo.c

# Target 3: t9_demo
t9_demo: t9_lib.o t9_demo.o
	$(CC) $(CFLAGS) -o $@ t9_lib.o t9_demo.o

# Clean up files after usage
clean:
	rm -f t9_demo.o t9_lib.o t9_demo
