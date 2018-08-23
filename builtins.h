#ifndef _BUILTINS_H
#define _BUILTINS_H

#include <limits.h>

#include "shell.h"
#include "shellvars.h"

#define BYTE 255

typedef struct builtin
{
	char *funcname;
	void (*func)(sev_t *);
} built_t;

void exit_sh(sev_t *sev);
void _printenv(sev_t *sev);
int check_builtin(sev_t *sev);

#endif	
