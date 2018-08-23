#ifndef _BUILTINS_H
#define _BUILTINS_H

#include "shell.h"
#include <limits.h>

typedef struct builtin
{
	char *funcname;
	void (*func)(int, list_t **mt);
} built_t;

void exit_sh(int signum, list_t **mt);
int check_builtin(char **av, list_t **mt);

#endif	
