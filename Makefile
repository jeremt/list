
#
# Config
#

AR ?= ar
CC ?= gcc
PREFIX ?= /usr/local

IFLAGS = -I inc

OFLAGS = -O3

CFLAGS = -std=c99 -Wall $(IFLAGS) $(OFLAGS)

SRC = \
	lib/list_at.c \
	lib/list_concat.c \
	lib/list_delete.c \
	lib/list_destroy.c \
	lib/list_each.c \
	lib/list_find.c \
	lib/list_insert.c \
	lib/list_join.c \
	lib/list_new.c \
	lib/list_slice.c

OBJ = $(SRC:.c=.o)

#
# Default rule
#

all: build/liblist.a

#
# Compilation rule
#

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@ -I lib

#
# Build the library
#

build/liblist.a: $(OBJ)
	@mkdir -p build
	$(AR) rc $@ $^

#
# Perform unit tests
#

bin/test: test/test.o $(OBJ)
	@mkdir -p bin
	$(CC) $^ -o $@

test: bin/test
	@./$<
	@echo $(CP)

#
# Run benchmarks
#

bin/benchmark: benchmark/benchmark.o $(OBJ)
	@mkdir -p bin
	$(CC) $^ -o $@

benchmark: bin/benchmark
	@./$<

#
# Run benchmarks
#

bin/example: example/example.o $(OBJ)
	@mkdir -p bin
	$(CC) $^ -o $@

example: bin/example
	@./$<

#
# Common rules
#

clean:
	$(RM) $(OBJ) test/*.o benchmark/*.o example/*.o

fclean: clean
	$(RM) -r build bin

re: fclean all

help:
	@echo ""
	@echo "  • \033[1mmake\033[m            build the library"
	@echo "  • \033[1mmake test\033[m       run unit tests"
	@echo "  • \033[1mmake benchmark\033[m  run benchmarks"
	@echo "  • \033[1mmake example\033[m    simple usage example"
	@echo ""

.PHONY: test benchmark example clean