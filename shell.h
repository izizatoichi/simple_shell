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
#define COLON ":"
#define BSLASH "\\"
#define FSLASH "/"
#define BUF_SIZE 1024
#define PS1 write(STDOUT_FILENO, "JS$ ", 4)
#define PS2 write(STDOUT_FILENO, "\nJS$ ", 5)
#define NEWLINE write(STDOUT_FILENO, "\n", 1)
#define LOGFILE ".simple_shell_history"

/**
 * struct sev_s - shell environment variables
 * @good2go: flag to continue or not continue with shell
 * @ia_mode: interactive mode - 1 yes, 0 no
 * @log: ptr to log link list for the current shell session
 * @log_cnt: number of log entries for the curent shell session
 * @mem: ptr to memory allocations for the current shell session
 * @env: ptr to the os environment variables
 * @input: ptr to the user's input
 * @p_input: ptr to the procssed input
 * @error: error number from current command
 * @errmsg: error message associated with the error number
 *
 * Description: Structure containing all the shell environment variables.
 * This one structure will be passed from function to function and contain
 * all the shell environment variables for the current session.
 */
typedef struct sev_s
{
	int good2go;
	int ia_mode;
	list_t *log;
	int log_cnt;
	list_t *mem;
	char **env;
	char *input;
	char **p_input;
	int error;
	char * errmsg;
} sev_t;

/* shellhelpers1.c */
void sig_handler(int signum);
void display_prompt(sev_t sev);
char *getcommand(sev_t *sev);
char **make_arr_str(char *s, const char *delim, sev_t *sev);
int action(sev_t *sev);


/* shellhelpers2.c */
char *_getenv(char *envar, sev_t *sev);
char *pathfinder(sev_t *sev);

/* shellhelpers3.c */
sev_t init_sev(char **ev);

/* _getline.c */
ssize_t _getline(char **lineptr, size_t *n, int fd, list_t **mt);

#endif /* _SHELL_H_ */
