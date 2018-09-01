CC=gcc

CFLAGS= -Wall -Werror -Wextra -pedantic
DIR= stringfiles/* builtinfiles/* errorfiles/*

all:
	$(CC) $(CFLAGS) *.c $(DIR) -o hsh
