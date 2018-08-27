#include "shell.h"

/**
 * change_dir - change directory
 * @sev: struct containing shell variables
 *
 * Description: Function changes current working directory to a user specified
 * directory. If no directory is given, then directory is changed to directory
 * in $HOME. User is also able to return to previous directory using a hyphen.
 * Return: void
 */
void change_dir(sev_t *sev)
{
	list_t **mt = &sev->mem;
	char *home = _getenv("HOME", sev), *envar = "PWD";
	char *targetdir = (sev->p_input)[1];
	char *pwd_to_print, *oldpwd = "OLDPWD", *oldcp = "OLDPWD";
	char cwd[4096];
	int ret_val;

	/* call getcwd with size 4096 buffer */
	reset_buffer(cwd, 4096);
	getcwd(cwd, 4096);
	if (!_getenv(oldpwd, sev))
	{
		oldpwd = _strcat(oldpwd, "=", mt);
		oldpwd = _strcat(oldpwd, cwd, mt);
		add_node(&sev->env, NULL, _strdup(oldpwd, mt));
	}

	/*
	 * if: dir is not given or user wants to go to home's parent dir,
	 * set target dir to home instead
	 *
	 * else if: user specifies hyphen, set target dir to old dir instead
	 */
	if (!targetdir)
		targetdir = home;

	else if (!_strcmp(targetdir, "-"))
	{
		targetdir = _getenv(oldpwd, sev);
		pwd_to_print = _strcat(targetdir, "\n", mt);
		write(STDOUT_FILENO, pwd_to_print, _strlen(pwd_to_print));
	}

	ret_val = chdir(targetdir);

	/* throw error message when chdir fails */
	if (ret_val == -1)
	{
		sev->error = 2;
		sev->errmsg = invaliddir(sev);
	}

	/* change pwd in env list and reset oldpwd */
	else
	{
	  	_setenv_helper(sev, oldcp, cwd);
		getcwd(cwd, 4096);
		_setenv_helper(sev, envar, cwd);
	}
}

/**
 * history - displays the user command history for the current session
 * @sev: ptr to the shell environment variable struct
 * Return: nothing
 */
void history(sev_t *sev)
{
	list_t *walker = NULL;
	char *entry = NULL;
	size_t counter = sev->log_cnt;
	unsigned int num_spaces = 0;

	reverse_list(&sev->log);
	walker = sev->log;
	while (walker)
	{
		counter--;
		walker = walker->next;
	}
	counter++;
	walker = sev->log;
	while (walker)
	{
		entry = _itoa(counter, &sev->mem);
		num_spaces = 5 - _strlen(entry);
		while (num_spaces)
		{
			entry = _strcat(SPACE, entry, &sev->mem);
			num_spaces--;
		}
		entry = _strcat(entry, SPACE, &sev->mem);
		entry = _strcat(entry, walker->value, &sev->mem);
		write (STDOUT_FILENO, entry, _strlen(entry));
		NEWLINE;
		counter++;
		walker = walker->next;
	}
	reverse_list(&sev->log);
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

/**
 * alias - assign and retrieve alias
 * @sev: struct of shell variables
 *
 * Description: Function allows for the assignment of a value to a variable.
 * The value is retrievable by using this function with the alias.
 * Return: void
 */
void alias(sev_t *sev)
{
	list_t **mt = &(sev->mem);
	char *key = NULL, *value = NULL, *arg = NULL, *arg_cp = NULL;
	char **av = sev->p_input;
	int i = 1, found = 1;

	if (!av[1])
		print_alias_val(sev, NULL, NULL, 1);

	while ((arg = av[i]))
	{
		arg_cp = _strdup(arg, mt);
		key = _strtok(arg_cp, EQUAL); 
		value = _strchr(arg, '=');
		if (value)
			value += 1;
		if (key && value)
		{
			if (!print_alias_val(sev, key, value, -1))
				add_node(&(sev->alias), key, value);
		}
		else if (key)
		{
			found = print_alias_val(sev, key, value, 0);
		}
		if (!found)
		{
			sev->error = 1; 
			sev->errmsg = invalidalias(sev, i);
			display_error(sev);
      		}
		i++;
		found = 1;
	}
}
