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

#include "./stringfile/string.h"
#include "linklist.h"
#include "./memofile/memo.h"
#include "shellvar.h"
#include "./builtinfile/builtin.h"
#include "./errorfile/error.h"
#include "./shellhelperfile/shellhelper.h"
#include "log.h"

#define SPACE " "
#define EQUAL "="
#define COLON ":"
#define BSLASH "\\"
#define FSLASH "/"
#define BUF_SIZE 4096
#define PS1 write(STDOUT_FILENO, "MANDALORIAN$ ", 4)
#define PS2 write(STDOUT_FILENO, "\nMANDALORIAN$ ", 5)
#define NEWLINE write(STDOUT_FILENO, "\n", 1)
#define DELIM " \t"

/* _getline.c */
ssize_t _getline(char **lineptr, size_t *n, int fd, list_t **mt);

#endif /* _SHELL_H_ */
