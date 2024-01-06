BIN = main
DIR = maze
FILES = $(shell ls $(DIR)/*.c)
FLAGS = -Wall -pedantic -std=c99
compile:
	@cc -c $(FLAGS) $(FILES)
	@cc main.c $(FLAGS) -o $(BIN) *.o
	@rm -rf *.o
	@echo "Compiled into \"$(BIN)\""
