#include "shell.h"

/**
 * _getenv - get environment variable
 * @envar: target environment variable
 * @env: list of environment variables
 * @mt: ptr to memory tracker link list
 *
 * Description: Function takes a list of env variables and returns env variable
 * if found.
 * Return: environment variable if found; otherwise, NULL
 */
char *_getenv(char *envar, char **env, list_t **mt)
{
	ssize_t i = 0, j = 0, len = 0;
	char *found = NULL;

	if (envar && *envar)
	{
		len = _strlen(envar);
		for (i = 0; env[i]; i++)
		{
			for (j = 0; j < len; j++)
				if (envar[j] != env[i][j])
					break;
			if (!envar[j])
			{
				found = _strdup(env[i], mt);
				return (_strpbrk(found, EQUAL) + 1);
			}
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
	char *fullpath = NULL, *ev_path = _getenv("PATH", ev, mt);
	char **pathlist = NULL;

	if (!ev_path)
		return (NULL);
	if (av)
	{
		if (av[0][0] == '/')
		{
			if (!access(av[0], X_OK))
				return (av[0]);
			return (NULL);
		}
		pathlist = make_arr_str(ev_path, COLON, mt);
		if (!pathlist)
			return (NULL);
		for (; *pathlist; pathlist++)
		{
			fullpath = _strcat(*pathlist, FSLASH, mt);
			fullpath = _strcat(fullpath, av[0], mt);
			if (!access(fullpath, X_OK))
				return (fullpath);
		}
	}
	return (NULL);
}
