CC=gcc

CFLAGS= -Wall -Werror -Wextra -pedantic

DIR= stringfiles/* builtinfiles/* errorfiles/* shellhelperfiles/* memoryfiles/*

all:
	$(CC) $(CFLAGS) *.c $(DIR) -o hsh
