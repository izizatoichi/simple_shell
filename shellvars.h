#ifndef _SHELLVARS_H_
#define _SHELLVARS_H_

#include "shell.h"

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
 * @olderror: error from previous command
 * @pid: pid of current shell
<<<<<<< HEAD
 * @alias: ptr to link list of all alias created by user
 * @shell_d: the path to directory where all files reside
 *
=======
 * @alias: ptr to the link list containing the aliases
 * @cmd_q: ptr to the list of commands in the queue
>>>>>>> b440dc0426993faa01d55a316908947c2b055451
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

} sev_t;

#endif /* _SHELLVARS_H_ */
