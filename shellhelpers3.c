#include "shell.h"

/**
 * init_sev - initialzies the shell environment variables
 * Return: the initialized values of type sev_t
 */
sev_t init_sev(void)
{
	sev_t init;

	init.good2go = 1;
	init.ia_mode = 1;
	init.log = NULL;
	init.log_cnt = 0;
	init.mem = NULL;
	init.env = NULL;
	init.input = NULL;
	init.p_input = NULL;
	init.error = 0;
	init.errmsg = NULL;

	return (init);
}

/**
 * read_env - read list of env and store in linked list
 * @sev: shell variable struct
 * @ev: list of environment variables
 *
 * Description: Function parses a list of env vars and stores each string in
 * linked list
 * Return: head of linked list
 */
list_t *read_env(sev_t *sev, char **ev)
{
	list_t **mt = &(sev->mem);
	list_t *head = NULL;

	for (; *ev; ev++)
		add_node(&head, _strdup(*ev, mt));

	return (head);
}
