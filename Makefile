.PHONY: all clean build test tags coverage run shuffle

all: clean build test

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean

build: tags
	clear
	$(MAKE) -C src build -j 8

test:
	clear
	$(MAKE) -C test test -j 8

shuffle:
	$(MAKE) -C test shuffle
tags:
	ctags --recurse=yes

coverage:
	rm -f src/*.gcda
	rm -f test/*.gcda
	rm -f src/*.gcno
	rm -f test/*.gcno
	$(MAKE) -C test clean
	$(MAKE) -C test test -j 8
	gcovr -r src

run: build
	$(MAKE) -C src run
