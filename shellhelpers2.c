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
char *_getenv(char *envar, char **env, list_t **mt)
{
        int len, i, j;
        char *keyword, *line;

        len = _strlen(envar);
        keyword = malloc(sizeof(char) * len);
	add_node(mt, (void *)keyword);
        if (!keyword)
                return (NULL);

        reset_buffer(keyword, len);

        for (i = 0; *env; i++, env++)
        {
                line = *env;

                for (j = 0; j < len; j++)
                        keyword[j] = line[j];

                if (!_strcmp(keyword, envar))
                {
                        free(keyword);
                        return (*env);
                }
        }
        free(keyword);
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
        char *ev_path = _getenv("PATH", ev, mt);
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
                pathlist = make_arr_str(paths, SEMICOLON, mt);
                if (!pathlist)
                        return (0);
                cmd = av[0];
		while (*pathlist)
                {
                        concatpath = _strcat_s(*pathlist, cmd, mt);
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
