
#
# Config
#

AR ?= ar
CC ?= gcc
PREFIX ?= /usr/local

CFLAGS = -O3 -std=c99 -Wall

SRC = lib/list.c

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
# Install/Uninstall the library
#

install: all
	cp -f build/liblist.a $(PREFIX)/lib/liblist.a
	cp -f src/list.h $(PREFIX)/include/list.h

uninstall:
	rm -f $(PREFIX)/lib/liblist.a
	rm -f $(PREFIX)/include/list.h

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
	@echo "  • \033[1mmake install\033[m    install the library into your system"
	@echo "  • \033[1mmake uninstall\033[m  uninstall the library into your system"
	@echo "  • \033[1mmake test\033[m       run unit tests"
	@echo "  • \033[1mmake benchmark\033[m  run benchmarks"
	@echo "  • \033[1mmake example\033[m    simple usage example"
	@echo ""

.PHONY: test benchmark clean install uninstall