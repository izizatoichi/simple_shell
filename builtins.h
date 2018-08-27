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

/* builtins1.c */
void exit_sh(sev_t *sev);
void _printenv(sev_t *sev);
void _setenv(sev_t *sev);
void _unsetenv(sev_t*sev);
int check_builtin(sev_t *sev);

/* builtins2.c */
void change_dir(sev_t *sev);
void history(sev_t *sev);
int print_alias_val(sev_t *sev, char *key, char *value, int flag);
void alias(sev_t *sev);

#endif
