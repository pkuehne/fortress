.PHONY: all clean build test tags coverage run

all: clean build test

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean

build: tags
	$(MAKE) -C src build

test:
	$(MAKE) -C test test

tags:
	ctags --recurse=yes

coverage:
	rm -f src/*.gcda
	rm -f test/*.gcda
	rm -f src/*.gcno
	rm -f test/*.gcno
	$(MAKE) -C test clean
	$(MAKE) -C test test
	gcovr -r src

run: build
	$(MAKE) -C src run
