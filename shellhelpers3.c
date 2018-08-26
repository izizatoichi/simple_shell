#include "shell.h"

/**
 * init_sev - initialzies the shell environment variables
 * Return: the initialized values of type sev_t
 */
sev_t *initialize_shell_env(sev_t *sev, char **ev)
{
	sev->good2go = 1;
	sev->ia_mode = isatty(STDIN_FILENO);
	sev->log = NULL;
	sev->log_cnt = 0;
	sev->mem = NULL;
	sev->env = NULL;
	sev->evp = ev;
	sev->input = NULL;
	sev->p_input = NULL;
	sev->error = 0;
	sev->errmsg = NULL;
	sev->oldpwd = NULL;
	sev->olderror = 0;
	sev->pid = getpid();

	sev->env = read_env(sev, ev);
	sev->oldpwd = _getenv("PWD", sev);
	sev->log_cnt = get_log_count(sev);

	signal(SIGINT, sig_handler);

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
	sev->olderror = sev->error;
	if (sev->error)
		write(STDOUT_FILENO, sev->errmsg, _strlen(sev->errmsg));
	if (sev->good2go)
	{
		sev->error = 0;
		sev->errmsg = NULL;
	}
}

/**
 * var_expansion - checks the inputs for $ and performs an expansion
 * @sev: ptr to the shell environment variable
 * Return: nothing
 */
void var_expansion(sev_t *sev)
{
	int index = 0;
	char *str = NULL;

	if (!sev->p_input)
		return;
	for (index = 0; sev->p_input[index]; index++)
	{
		if (sev->p_input[index][0] == '$')
		{
			str = sev->p_input[index];
			if (!_strcmp(sev->p_input[index], "$$"))
				str = _itoa(sev->pid, &sev->mem);
			else if (!_strcmp(sev->p_input[index], "$?"))
				str = _itoa(sev->olderror, &sev->mem);
			else if (sev->p_input[index][0] == '$')
				str = _getenv(sev->p_input[index] + 1, sev);
			sev->p_input[index] = str;
		}
	}
	if (!_strcmp(sev->p_input[0], "cd"))
	{
		if (sev->p_input[1] && sev->p_input[1][0] == '~')
		{
			str = _getenv("HOME", sev);
			str = _strcat(str, sev->p_input[1] + 1, &sev->mem);
			sev->p_input[1] = str;
		}
	}
}
