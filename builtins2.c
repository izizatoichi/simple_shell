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
	//list_t *ev = sev->env;
	list_t **mt = &(sev->mem);
	char *home = _getenv("HOME", sev), *envar = "PWD";
	char *targetdir = (sev->p_input)[1];
       //	*str = NULL;
	char *pwd_to_print, *oldpwd = "OLDPWD", *oldcp = "OLDPWD";
	char cwd[4096];
	int ret_val;
	//unsigned int i;

	/* call getcwd with size 4096 buffer */
	reset_buffer(cwd, 4096);
	getcwd(cwd, 4096);
	if (!_getenv(oldpwd, sev))
	{
		oldpwd = _strcat(oldpwd, "=", mt);
		oldpwd = _strcat(oldpwd, cwd, mt);
		add_node(&(sev->env), (void *)_strdup(oldpwd, mt));	
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
		/*
		for (ev = sev->env; ev; ev = ev->next)
		{
			str = ev->dataptr;
			for (i = 0; i <_strlen(oldcp); i++)
				if (oldcp[i] != str[i])
					break;
			if (!oldcp[i])
			{
				oldcp = _strcat(oldcp, "=", mt);
				oldcp = _strcat(oldcp, cwd, mt);
				ev->dataptr = _strdup(oldcp, mt);
				break;
			}
		}
		*/
	  	_setenv_helper(sev, oldcp, cwd);
		getcwd(cwd, 4096);

		/*
		for (ev = sev->env; ev; ev = ev->next)
		{
			str = ev->dataptr;
			for (i = 0; i < _strlen(envar); i++)
				if (envar[i] != str[i])
					break;
			if (!envar[i])
			{
				envar = _strcat(envar, "=", mt);
				envar = _strcat(envar, cwd, mt);
				ev->dataptr = _strdup(envar, mt);
				break;
			}
		}*/

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
		entry = _strcat(entry, walker->dataptr, &sev->mem);
		write (STDOUT_FILENO, entry, _strlen(entry));
		NEWLINE;
		counter++;
		walker = walker->next;
	}
	reverse_list(&sev->log);
}
