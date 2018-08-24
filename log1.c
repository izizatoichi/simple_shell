#include "log.h"

/**
 * add_log - add input from user to log
 * @sev: ptr to shell environment variable link list
 * Return: 1 for success, 0 for fail
 */
int add_log(sev_t *sev)
{
        if (add_node(&sev->log, _strdup(sev->input, &sev->mem)))
	{
		sev->log_cnt++;
		return (1);
	}
	return (0);
}

/**
 * write_log - writes the current sessions' log to a file
 * @sev: ptr to the shell environment variable
 * Return: 1 if success, 0 for fail
 */
int write_log(sev_t *sev)
{
	(void)sev;
	return (0);
}
