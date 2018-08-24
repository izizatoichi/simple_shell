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
	ssize_t j = 0, len = 0;
	char *found = NULL, *str;
	list_t *env = sev->env;

	if (envar && *envar)
	{
		len = _strlen(envar);
		for (; env; env = env->next)
		{
			str = env->dataptr;
			for (j = 0; j < len; j++)
				if (envar[j] != str[j])
					break;
			if (!envar[j])
			{
				found = _strdup(str, &(sev->mem));
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

/**
 * add_log - add input from user to log
 * @sev: ptr to shell environment variable link list
 * Return: nothing
 */
void add_log(sev_t *sev)
{
	add_node(&sev->log, _strdup(sev->input, &sev->mem));
	sev->log_cnt++;
}

/**
 * clean_sev - go through and free the link lists in the sev
 * @sev: ptr to the shell environment variable link list
 * Return: nothing
 */
void clean_sev(sev_t *sev)
{
	free_list(&sev->mem, 1);
	free_list(&sev->log, 0);
	free_list(&sev->env, 0);
}

/**
 * make_evp_arr - makes the enviroment varaible array from the in memory
 * copy
 * @sev: ptr to the shell environment variable link list
 * Return: ptr to the constucted environment array
 */
char **make_evp_arr(sev_t *sev)
{
	char **evp = NULL;
	int entries = 0, i = 0;
	list_t *walker = sev->env;

	while (walker)
	{
		entries++;
		walker = walker->next;
	}
	evp = malloc(sizeof(char *) * (entries + 1));
	if (!evp)
		return (NULL);
	add_node(&sev->mem, evp);
	walker = sev->env;
	for (i = 0; walker; i++)
	{
		evp[i] = (char *)walker->dataptr;
		walker = walker->next;
	}
	evp[i] = NULL;

	return (evp);
}
