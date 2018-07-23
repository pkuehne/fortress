.PHONY: all clean build test coverage run shuffle test lint validate

LOG_DIR=artifacts/logs/

all: clean build test run

clean:
	@$(MAKE) -C src clean
	@$(MAKE) -C test clean

build: 
	@$(MAKE) -C src build -j 8

test: 
	@$(MAKE) -C test build -j 8
	@echo "Starting tests"
	@./unit_tests --gtest_shuffle

coverity:
	cov-build --dir cov-int $(MAKE) build
	tar czvf fortress.tgz cov-int
	
coverage:
	rm -f src/*.gcda
	rm -f test/*.gcda
	rm -f src/*.gcno
	rm -f test/*.gcno
	$(MAKE) -C test clean
	$(MAKE) -C test build -j 8 COVERAGE=Y
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

docs:
	doxygen Doxyfile
	cp -r doxygen/html/* /var/www/html/fortress/

lint:
	cppcheck src/ --enable=style,information,warning --error-exitcode=1 -DMAJOR=1 --std=c++11 2>lint-errors.txt

validate: build test lint
	@echo "Validation succeeded!"