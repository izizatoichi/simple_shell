#include "shell.h"

/**
 * _getenv - get environment variable
 * @envar: target environment variable
 * @env: list of environment variables
 *
 * Description: Function takes a list of env variables and returns env variable
 * if found.
 * Return: environment variable if found; otherwise, NULL
 */
char *_getenv(char *envar, sev_t *sev)
{
	ssize_t i = 0, j = 0, len = 0;
	char *found = NULL;

	if (envar && *envar)
	{
		len = _strlen(envar);
		for (i = 0; sev->env[i]; i++)
		{
			for (j = 0; j < len; j++)
				if (envar[j] != sev->env[i][j])
					break;
			if (!envar[j])
			{
				found = _strdup(sev->env[i], &(sev->mem));
				return (_strpbrk(found, EQUAL) + 1);
			}
		}
	}
        return (NULL);
}

/**
 * pathfinder - determines if a command is in path
 * @sev: shell environment variable struct
 *
 * Description: Function takes a list of arguments and uses the first argument
 * to determine if the argument is an executable in a directory of PATH
 * environment variable. Function will return the path to the executable if
 * process has access executable permission to the file. Otherwise, function
 * returns NULL.
 * Return: Path to executable or NULL
 */
char *pathfinder(sev_t *sev)
{
	char *fpath = NULL, *ev_path = _getenv("PATH", sev);
	char **pathlist = NULL;

	if (!ev_path)
		return (NULL);
	if (sev->p_input)
	{
		if (sev->p_input[0][0] == '/')
		{
			if (!access(sev->p_input[0], X_OK))
				return (sev->p_input[0]);
			return (NULL);
		}
		pathlist = make_arr_str(ev_path, COLON, sev);
		if (!pathlist)
			return (NULL);
		for (; *pathlist; pathlist++)
		{
			fpath = _strcat(*pathlist, FSLASH, &(sev->mem));
			fpath = _strcat(fpath, sev->p_input[0], &(sev->mem));
			if (!access(fpath, X_OK))
				return (fpath);
		}
	}
	return (NULL);
}
