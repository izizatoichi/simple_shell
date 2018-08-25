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
	list_t *ev = sev->env;
	list_t **mt = &(sev->mem);
	char *home = _getenv("HOME", sev), *envar = "PWD";
	char *targetdir = (sev->p_input)[1], *str = NULL;
	char *pwd_to_print;
	char cwd[4096];
	int ret_val;
	unsigned int i;

	/* call getcwd with size 4096 buffer */
	reset_buffer(cwd, 4096);
	getcwd(cwd, 4096);

	/*
	 * if: dir is not given or user wants to go to home's parent dir,
	 * set target dir to home instead
	 *
	 * else if: user specifies hyphen, set target dir to old dir instead
	 */
	if (!targetdir || (!_strcmp(targetdir, "..") && !_strcmp(home, cwd)))
		targetdir = home;
	else if (!_strcmp(targetdir, "-"))
	{
		targetdir = sev->oldpwd;
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
		for (; ev; ev = ev->next)
		{
			str = ev->dataptr;
			for (i = 0; i < _strlen(envar); i++)
				if (envar[i] != str[i])
					break;
			if (!envar[i])
			{
				envar = _strcat(envar, "=", mt);
				envar = _strcat(envar, targetdir, mt);
				ev->dataptr = _strdup(envar, mt);
				break;
			}
		}
		sev->oldpwd = _strdup(cwd, mt);
	}
}
