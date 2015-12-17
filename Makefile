test: FORCE
		@echo "\nCompiling the SQL parser and the tests...\n"
		@make clean -C src/ >/dev/null || exit 1
		@make tests -C src/ >/dev/null || exit 1
		@make grammar_test -C src/ >/dev/null || exit 1
		@echo "Running tests..."
		@./bin/grammar_test -f "src/tests/valid_queries.sql"
		@./bin/tests


build: FORCE
		@echo "\nBuilding the SQL parser... (Run tests with 'make test')"
		@echo "Build directory: build/\n"
		make -C src/

all: config.c
		@echo "Building the configuration file..."
		gcc -Wall -lconfig -o config config.c

docs: FORCE
		doxygen docs/doxy.conf

