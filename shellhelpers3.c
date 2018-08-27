#include "shell.h"

/**
 * init_sev - initialzies the shell environment variables
 * Return: the initialized values of type sev_t
 */
sev_t *initialize_shell_env(sev_t *sev, char **ev)
{
	char cwd[4096];
	reset_buffer(cwd, 4096);

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
	sev->olderror = 0;
	sev->pid = getpid();
	sev->alias = NULL;
	sev->shell_d = NULL;

	sev->env = read_env(sev, ev);
	sev->log_cnt = get_log_count(sev);
	sev->shell_d = _strdup(getcwd(cwd, 4096), &(sev->mem));

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
		add_node(&head, NULL, _strdup(*ev, mt));

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
		write(STDERR_FILENO, sev->errmsg, _strlen(sev->errmsg));
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

/**
 * print_alias_val - prints and retrieves alias
 * @sev: struct of shell variables
 * @key: alias
 * @value: value stored in alias
 * @flag: a flag to modify function's performance
 *
 * Description: Function has three modes: print specific alias (flag = 0),
 * set alias if alias exists (flag = -1), and print all aliases (flag != -1 &&
 * flag != 0). Using the key and value inputs, function is able to parse
 * through alias linked list and perform desired functionality.
 * Return: 1 for success/found, 0 for failure/not found. 
 */
int print_alias_val(sev_t *sev, char *key, char *value, int flag)
{
	list_t *alias = reverse_list(&(sev->alias));
	list_t **mt = &(sev->mem);
	char *argstr = NULL;
	int success = 0;

	for (; alias; alias = alias->next)
	{
		argstr = alias->key;
		if (!flag)
		{
			if (!_strcmp(argstr, key))
			{
				argstr = _strcat(argstr, "='", mt);
				argstr = _strcat(argstr, alias->value, mt);
				argstr = _strcat(argstr, "'\n", mt);
				write(STDOUT_FILENO, argstr, _strlen(argstr));
				alias = reverse_list(&(sev->alias));
				return (1);
			}
		}
		else if (flag == -1)
		{
			if (!_strcmp(argstr, key))
			{
				alias->value = value;
				alias = reverse_list(&(sev->alias));
				return (1);
			}
		}	
		else
		{
			argstr = _strcat(argstr, "='", mt);
			argstr = _strcat(argstr, alias->value, mt);
			argstr = _strcat(argstr, "'\n", mt);
			write(STDOUT_FILENO, argstr, _strlen(argstr));
			success = 1;
		}
	}
	alias = reverse_list(&(sev->alias));
	return (success);
}
