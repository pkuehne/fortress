.PHONY: all clean build test coverage run shuffle

LOG_DIR=artifacts/logs/

all: clear clean build test run

clear:
	clear
clean:
	@$(MAKE) -C src --no-print-directory clean
	@$(MAKE) -C test --no-print-directory clean

build: clear
	@$(MAKE) -C src --no-print-directory build -j 8

test:
#	@$(MAKE) -C test --no-print-directory test -j 8

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
	sudo mkdir -p /usr/games/fortress
	sudo mkdir -p /usr/games/fortress/artifacts
	sudo mkdir -p /usr/games/fortress/artifacts/logs
	sudo cp ./fortress /usr/games/fortress
	sudo cp -r ./graphics/ /usr/games/fortress
	sudo cp -r ./config/ /usr/games/fortress

doxy:
	doxygen Doxyfile
	cp -r doxygen/html/* /var/www/html/fortress/
