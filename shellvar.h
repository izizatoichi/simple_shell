#ifndef _SHELLVAR_H_
#define _SHELLVAR_H_

#include "shell.h"

/**
 * struct sev_s - shell environment variables
 * @skywalker: flag to continue or not continue with shell
 * @ia_mode: interactive mode - 1 yes, 0 no
 * @log: ptr to log link list for the current shell session
 * @log_cnt: number of log entries for the curent shell session
 * @cmd_cnt: cmd counter separate from log counter
 * @mem: ptr to memory allocations for the current shell session
 * @env: ptr to the os environment variables
 * @evp: ptr to environment variables in array
 * @input: ptr to the user's input
 * @p_input: ptr to the procssed input
 * @error: error number from current command
 * @errmsg: error message associated with the error number
 * @olderror: error from previous command
 * @pid: pid of current shell
 * @alias: ptr to link list of all alias created by user
 * @cmd_q: ptr to the list of commands in the queue
 * @shell_d: current working directory
 * @arg0: command executed to run shell
 * Description: Struct contain all the shell env vars.
 * This one struct will be passed from func to func and contain
 * all the shell env vars for the current session.
 */
typedef struct sev_s
{
	int skywalker;
	int ia_mode;
	list_t *log;
	int log_cnt;
	int cmd_cnt;
	list_t *mem;
	list_t *env;
	char **evp;
	char *input;
	char **p_input;
	int error;
	char *errmsg;
	int olderror;
	pid_t pid;
	list_t *alias;
	list_t *cmd_q;
	char *shell_d;
	char *arg0;
} sev_t;

#endif /* _SHELLVAR_H_ */
