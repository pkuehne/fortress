.PHONY: all clean build test coverage run shuffle

LOG_DIR=artifacts/logs/

all: clean build test coverity doxy run install

clean:
	@$(MAKE) -C src --no-print-directory clean
	@$(MAKE) -C test --no-print-directory clean

build: 
	@$(MAKE) -C src --no-print-directory build -j 8

test:
	@$(MAKE) -C test --no-print-directory test -j 8

shuffle:
	@$(MAKE) -C test --no-print-directory shuffle

coverity:
	cov-build --dir cov-int $(MAKE) build
	tar czvf fortress.tgz cov-int
	
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
