#ifndef _SHELL_H_
#define _SHELL_H_

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "strings.h"
#include "linklists.h"
#include "memory.h"
#include "shellvars.h"
#include "builtins.h"
#include "errors.h"
#include "log.h"

#define SPACE " "
#define EQUAL "="
#define COLON ":"
#define BSLASH "\\"
#define FSLASH "/"
#define BUF_SIZE 1024
#define PS1 write(STDOUT_FILENO, "JS$ ", 4)
#define PS2 write(STDOUT_FILENO, "\nJS$ ", 5)
#define NEWLINE write(STDOUT_FILENO, "\n", 1)
#define DELIM " \t"

/* shellhelpers1.c */
void sig_handler(int signum);
void display_prompt(sev_t sev);
char *getcommand(sev_t *sev);
char **make_arr_str(char *s, const char *delim, sev_t *sev);
int action(sev_t *sev);

/* shellhelpers2.c */
char *_getenv(char *envar, sev_t *sev);
char *pathfinder(sev_t *sev);
void clean_sev(sev_t *sev);
char **make_evp_arr(sev_t *sev);
int _setenv_helper(sev_t *sev, char *tofind, char *cwd);

/* shellhelpers3.c */
sev_t *initialize_shell_env(sev_t *sev, char **ev);
list_t *read_env(sev_t *sev, char **ev);
void display_error(sev_t *sev);
void var_expansion(sev_t *sev);
int print_alias_val(sev_t *sev, char *key, char *value, int flag);

/* shellhelpers4.c */
void process_input(char *cmd, sev_t *sev);
void display_banner(int ia_mode);
void stripquotes(sev_t *sev);

/* _getline.c */
ssize_t _getline(char **lineptr, size_t *n, int fd, list_t **mt);

#endif /* _SHELL_H_ */
