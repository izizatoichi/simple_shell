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
	else if (targetdir[0] == '-')
	{
		sev->errmsg = illegaloptions(sev);
		sev->error = 1;
		return;
	}

	ret_val = chdir(targetdir);

	/* throw error message when chdir fails */
	if (ret_val == -1)
	{
		sev->error = 1;
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
		write(STDOUT_FILENO, entry, _strlen(entry));
		NEWLINE;
		counter++;
		walker = walker->next;
	}
	reverse_list(&sev->log);
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
	char *key = NULL, *value = NULL, *arg = NULL, *arg_cp = NULL, *token = NULL;
	char **av = sev->p_input;
	int i = 1, found = 1, error = 0;

	if (!av[1])
		print_alias_val(sev, NULL, NULL, 1);

	while ((arg = av[i]))
	{
		arg_cp = _strdup(arg, mt);

		if (arg_cp)
		{
			if (arg_cp[0] == '=')
			{
				key = _strcat(key, "=", mt);
				token = _strtok(arg_cp + 1, EQUAL);
				key = _strcat(key, token, mt);

				value = _strchr(arg + 1, '=');
				if (value)
					value += 1;
			}

			else
			{
				key = _strtok(arg_cp, EQUAL);
				value = _strchr(arg, '=');

				if (value)
					value += 1;
			}
		}
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
			sev->errmsg = invalidalias(sev, i);
			sev->error = 1;
			display_error(sev);
			error = 1;
		}
		i++;
		found = 1;
	}
	sev->error = error;
}

/**
 * _help - display help for builtin
 * @sev: struct containing shell variables
 *
 * Description: Function checks if argument is a valid builtin. If so, display
 * help for the command. Otherwise, display error.
 * Return: void
 */
void _help(sev_t *sev)
{
	list_t **mt = &(sev->mem);
	char *filepath = NULL, *file = NULL, *arg = NULL;
	char buf[BUF_SIZE];
	char **av = sev->p_input;
	int infile = 0, r_val = 0, w_val = 0, i = 0;

	help_t help_l[] = {
		{"exit", "help_exit"},
		{"env", "help_env"},
		{"setenv", "help_setenv"},
		{"unsetenv", "help_unsetenv"},
		{"cd", "help_cd"},
		{"history", "help_history"},
		{"alias", "help_alias"},
		{"help", "help_help"},
		{NULL, NULL}
	};

	if (av && *av)
	{
		arg = av[1];

		if (!arg)
		{
			goto skip;
		}

		for (i = 0; help_l[i].arg; i++)
		{
			if (!_strcmp(arg, help_l[i].arg))
			{
				file = help_l[i].file;
				break;
			}
		}

		filepath = _strdup(sev->shell_d, mt);
		filepath = _strcat(filepath, "/", mt);
skip:

		if (arg)
			filepath = _strcat(filepath, file, mt);
		else
			filepath = _strcat(filepath, "help_main", mt);

		infile = open(filepath, O_RDONLY);

		r_val = read(infile, buf, BUF_SIZE);

		if (r_val == -1)
		{
			sev->errmsg = helpfilenotfound(sev);
			sev->error = 1;
			r_val = 0;
		}

		while (r_val)
		{
			w_val = write(STDOUT_FILENO, buf, r_val);

			if (w_val == -1)
			{
				sev->errmsg = "Error!\n";
				sev->error = 1;
				break;
			}
			r_val = read(infile, buf, BUF_SIZE);
		}

		close(infile);
	}
}
