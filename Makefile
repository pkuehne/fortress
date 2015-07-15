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

doxy:
	doxygen Doxyfile

pages:
	git checkout gh-pages
	git reset --hard master
	$(MAKE) doxy
	git add doxygen/*
	git commit -m"Updated documentation"
	git push origin gh-pages --force
	git checkout master
    
