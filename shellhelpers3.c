#include "shell.h"

/**
 * init_sev - initialzies the shell environment variables
 * Return: the initialized values of type sev_t
 */
sev_t *initialize_shell_env(sev_t *sev, char **ev)
{
	sev->good2go = 1;
	sev->ia_mode = 1;
	sev->log = NULL;
	sev->log_cnt = 0;
	sev->mem = NULL;
	sev->env = NULL;
	sev->evp = ev;
	sev->input = NULL;
	sev->p_input = NULL;
	sev->error = 0;
	sev->errmsg = NULL;

	sev->env = read_env(sev, ev);

	return (sev);
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

/**
 * display_error - display the error
 * @sev: ptr to the shell environment variable link list
 * Return: nothing
 */
void display_error(sev_t *sev)
{
	if (sev->error)
		write(STDOUT_FILENO, sev->errmsg, _strlen(sev->errmsg));
	sev->error = 0;
	sev->errmsg = NULL;
}
