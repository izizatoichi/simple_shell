#ifndef _BUILTINS_H
#define _BUILTINS_H

#include <limits.h>

#include "shell.h"
#include "shellvars.h"

#define BYTE 255
#define BUF_SIZE 4096

/**
 * struct builtin - struct containing function name and its respective function
 * @funcname: name of function
 * @func: function to be called when funcname is invoked
 *
 * Description: struct of function name and its respective function
 */
typedef struct builtin
{
	char *funcname;
	void (*func)(sev_t *);
} built_t;

/**
 * struct help_list - struct of argument and help file
 * @arg: argument string
 * @file: the path of file
 *
 * Description: Struct contains string arg and the path to the file here its
 * help description is found
 */
typedef struct help_list
{
	char *arg;
	char *file;
} help_t;

/* builtins1.c */
void exit_sh(sev_t *sev);
void _printenv(sev_t *sev);
void _setenv(sev_t *sev);
void _unsetenv(sev_t *sev);
int check_builtin(sev_t *sev);

/* builtins2.c */
void change_dir(sev_t *sev);
void history(sev_t *sev);
void alias(sev_t *sev);
void _help(sev_t *sev);

#endif
