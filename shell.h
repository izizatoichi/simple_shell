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

#define SPACE " "
#define EQUAL "="
#define SEMICOLON ":"
#define BUF_SIZE 1024
#define PS1 write(STDOUT_FILENO, "JS$ ", 4)
#define NEWLINE write(STDOUT_FILENO, "\n", 1)

/* shellhelpers1.c */
char *getcommand(list_t **mt);
char **make_arr_str(char *s, const char *delim, list_t **mt);
int action(char **cv, list_t **mt);
void sig_handler(int signum);

/* shellhelpers2.c */
char *_getenv(char *envar, char **env, list_t **mt);
char *pathfinder(char **av, char **ev, list_t **mt);

/* _getline.c */
ssize_t _getline(char **lineptr, size_t *n, int fd, list_t **mt);

#endif /* _SHELL_H_ */
