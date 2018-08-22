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
        char *ev_path = _getenv("PATH", ev);
        char **splitlist = NULL, **pathlist = NULL;
        char *cmd = NULL, *paths = NULL, *concatpath;

        if (!ev_path)
                return (0);
        if (av)
        {
                splitlist = make_arr_str(ev_path, EQUAL, mt);
                if (!splitlist)
                        return (0);
                paths = splitlist[1];
                pathlist = make_arr_str(paths, COLON, mt);
                if (!pathlist)
                        return (0);
                cmd = av[0];
		while (*pathlist)
                {
                        concatpath = _strcat(*pathlist, BACKSLASH, mt);
			concatpath = _strcat(*pathlist, cmd, mt);
                        if (!access(concatpath, X_OK))
                        {
                                return (concatpath);
                        }
                        free(concatpath);
                        pathlist++;
                }
        }
        return (NULL);
}
