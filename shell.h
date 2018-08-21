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
#define BUF_SIZE 1024
#define PS1 write(STDOUT_FILENO, "JS$ ", 4)

/* shellhelpers1.c */
char *getcommand(void);
char **make_arr_str(char *s, const char *delim);
int action(char **cv);
void sig_handler(int signum);

/* _getline.c */
ssize_t _getline(char **lineptr, size_t *n, int fd);

#endif /* _SHELL_H_ */
