#ifndef _BUILTIN_H
#define _BUILTIN_H

#include <limit.h>

#include "../shell.h"
#include "../shellvar.h"

#define BYTE 255
#define BUF_SIZE 4096

/**
 * struct builtin - struct containing func name
 * @funcname: name of func
 * @func: func to be called when name is invoked
 *
 * Description: struct of func name and its respective func
 */
typedef struct builtin
{
	char *funcname;
	void (*func)(sev_t *);
} built_t;

/**
 * struct help_list - structure of argument and help file
 * @arg: arg string
 * @file: path of file
 *
 * Description: Struct contain str arg and path to the file where its
 * help description is found
 */
typedef struct help_list
{
	char *arg;
	char *file;
} help_t;

/* builtin01.c */
void exit_sh(sev_t *sev);
void _printenv(sev_t *sev);
void _setenv(sev_t *sev);
void _unsetenv(sev_t *sev);
int check_builtin(sev_t *sev);

/* builtin02.c */
void change_dir(sev_t *sev);
void history(sev_t *sev);
void alias(sev_t *sev);
void _help(sev_t *sev);

#endif
