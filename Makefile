.PHONY: all clean build test tags coverage run shuffle

LOG_DIR=artifacts/logs/

all: clean build test

clean:
	@$(MAKE) -C src --no-print-directory clean
	@$(MAKE) -C test --no-print-directory clean

build: tags
	clear
	@$(MAKE) -C src --no-print-directory build -j 8

test:
	clear
	@$(MAKE) -C test --no-print-directory test -j 8

shuffle:
	@$(MAKE) -C test --no-print-directory shuffle

tags:
	@ctags --recurse=yes

coverage:
	rm -f src/*.gcda
	rm -f test/*.gcda
	rm -f src/*.gcno
	rm -f test/*.gcno
	$(MAKE) -C test --no-print-directory clean
	$(MAKE) -C test --no-print-directory test -j 8 COVERAGE=Y
	gcovr -r src

run: build $(LOG_DIR)
	@echo "Starting FORTRESS"
	@./fortress

$(LOG_DIR):
	@mkdir -p artifacts/logs

install: build

doxy:
	doxygen Doxyfile
	cp -r doxygen/html/* /var/www/html/fortress/
