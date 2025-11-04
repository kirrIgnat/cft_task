CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -Iinclude

OBJS    = src/core.o src/io.o src/util.o

all: task task_test

task: $(OBJS) src/main.o
	$(CC) $(CFLAGS) -o $@ $^

task_test: $(OBJS) tests/main.o tests/cases.o
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o tests/*.o task task_test

.PHONY: all clean
