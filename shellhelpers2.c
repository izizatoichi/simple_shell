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
char *_getenv(char *envar, char **env)
{
	ssize_t i = 0, len = 0;

	if (envar && *envar)
	{
		len = _strlen(envar);
		for (; *env; env++)
		{
			for (i = 0; i < len; i++)
				if (envar[i] != (*env)[i])
					break;
			if (!envar[i])
				return (_strpbrk(*env, EQUAL) + 1);
		}
	}
        return (NULL);
}

/**
 * pathfinder - determines if a command is in path
 * @av: list of arguments
 * @ev: list of environment variables
 * @mt: double ptr to memory tracker link list
 *
 * Description: Function takes a list of arguments and uses the first argument
 * to determine if the argument is an executable in a directory of PATH
 * environment variable. Function will return the path to the executable if
 * process has access executable permission to the file. Otherwise, function
 * returns NULL.
 * Return: Path to executable or NULL
 */
char *pathfinder(char **av, char **ev, list_t **mt)
{
	char *cmd = NULL, *fullpath = NULL, *ev_path = _getenv("PATH", ev);
	char **pathlist = NULL;

	if (!ev_path)
		return (NULL);
	if (av)
	{
		pathlist = make_arr_str(ev_path, COLON, mt);
		if (!pathlist)
			return (NULL);
		for (; *pathlist; pathlist++)
		{
			fullpath = _strcat(*pathlist, BACKSLASH, mt);
			fullpath = _strcat(*pathlist, av[0], mt);
			if (!access(fullpath, X_OK))
				return (fullpath);
		}
	}
	return (NULL);
}
