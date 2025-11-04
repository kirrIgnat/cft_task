CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Iinclude

OBJ = src/core.o src/io.o src/util.o

all: statdump statdump_test

statdump: $(OBJ) src/main.o
	$(CC) $(CFLAGS) -o $@ $^

statdump_test: $(OBJ) tests/main.o tests/cases.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f src/*.o tests/*.o task task_test
