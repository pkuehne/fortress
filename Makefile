.PHONY: all clean build test tags coverage run shuffle

all: clean build test

clean:
	$(MAKE) -C src --no-print-directory clean
	$(MAKE) -C test --no-print-directory clean

build: tags
	clear
	$(MAKE) -C src --no-print-directory build -j 8

test:
	clear
	$(MAKE) -C test --no-print-directory test -j 8

shuffle:
	$(MAKE) -C test --no-print-directory shuffle
tags:
	ctags --recurse=yes

coverage:
	rm -f src/*.gcda
	rm -f test/*.gcda
	rm -f src/*.gcno
	rm -f test/*.gcno
	$(MAKE) -C test --no-print-directory clean
	$(MAKE) -C test --no-print-directory test -j 8
	gcovr -r src

run: build
	$(MAKE) -C src --no-print-directory run

doxy:
	doxygen Doxyfile
	cp -r doxygen/html/* /var/www/html/fortress/

pages:
	git checkout gh-pages --force
	git reset --hard master
	$(MAKE) --no-print-directory doxy
	git add doxygen/*
	git commit -m"Updated documentation"
	git push origin gh-pages --force
	git checkout master
    
