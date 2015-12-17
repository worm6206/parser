

BUILD_DIR = ../build/
BIN_DIR = ../bin

CC = g++
CFLAGS = -O3 -I./ -Ilib/ -Ilib/statements/ -Iparser/ -std=c++11 -pthread -Wall -g

LIB_HEADERS = $(shell find lib/ -name '*.h') parser/bison_parser.h parser/flex_lexer.h parser/SQLParser.h parser/parser_typedef.h
LIB_SOURCES = $(shell find lib/ -name '*.cpp') parser/bison_parser.cpp parser/flex_lexer.cpp parser/SQLParser.cpp
TEST_SOURCES = $(shell find tests/ -name '*.cpp')


build: clean
	make -C parser/
	mkdir $(BUILD_DIR)
	cp $(LIB_SOURCES) $(BUILD_DIR)
	cp $(LIB_HEADERS) $(BUILD_DIR)

grammar_test: $(LIB_SOURCES) sql_grammar_test.cpp
	$(CC) $(CFLAGS) $(LIB_SOURCES) sql_grammar_test.cpp -o $(BIN_DIR)/grammar_test

token: $(LIB_SOURCES) token.cpp
	$(CC) $(CFLAGS) $(LIB_SOURCES) token.cpp -o $(BIN_DIR)/token

tests: $(LIB_SOURCES) $(TEST_SOURCES) sql_tests.cpp
	$(CC) $(CFLAGS) $(LIB_SOURCES) $(TEST_SOURCES) sql_tests.cpp -o $(BIN_DIR)/tests

kevin: $(LIB_SOURCES) $(TEST_SOURCES) kevin.cpp
	$(CC) $(CFLAGS) $(LIB_SOURCES) kevin.cpp -o $(BIN_DIR)/kevin

all: config.c
		@echo "Building the configuration file..."
		gcc -Wall -lconfig -o config config.c

run: config
		../bin/token "SELECT * FROM region JOIN nation ON region.itemID = nation.ID;" && ./config && vim config.conf

parser/bison_parser.cpp:
	make -C parser/

clean:
	rm -f *.o *~ $(BIN_DIR)/analysis $(TESTS_BIN) $(BIN_DIR)/grammar_test $(BIN_DIR)/tests $(BIN_DIR)/token
	rm -rf $(BUILD_DIR)
	make clean -C parser/


test: tests grammar_test
	@./$(BIN_DIR)/grammar_test -f ../test/valid_queries.sql
	@./$(BIN_DIR)/tests