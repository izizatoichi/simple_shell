#include "../shell.h"

/**
 * _getenv - get environment variable
 * @envar: target environment variable
 * @sev: struct containing shell variables
 *
 * Description: Function takes a list of env variables and returns env variable
 * if found.
 * Return: environment variable if found; otherwise, NULL
 */
char *_getenv(char *envar, sev_t *sev)
{

	ssize_t j = 0;
	char *found = NULL, *str;
	list_t *env = sev->env;

	if (envar && *envar)
	{
		for (; env; env = env->next)
		{
			str = env->value;
			for (j = 0; envar[j] && str[j]; j++)
				if (envar[j] != str[j])
					break;
			if (!envar[j] && str[j] == '=')
			{
				found = _strdup(str, &sev->mem);
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
	char *cmd = NULL;
	char **pathlist = NULL;
	DIR *dp = NULL;

	if (sev->p_input && sev->p_input[0])
		cmd = sev->p_input[0];
	if (!_strcmp(cmd, "."))
		return (NULL);
	dp = opendir(sev->p_input[0]);
	if (dp)
	{
		closedir(dp);
		sev->error = 126;
		permdenied(sev);
		return (NULL);
	}
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (cmd);
			sev->error = 126;
			permdenied(sev);
		}
		else
		{
			if (!sev->error)
			{
				sev->error = 127;
				filenotfound(sev);
			}
		}
		return (NULL);
	}
	if (ev_path)
		pathlist = make_arr_str(ev_path, COLON, sev);
	else
	{
		sev->error = 127;
		filenotfound(sev);
		return (NULL);
	}
	if (!pathlist || !*pathlist)
	{
		sev->error = 127;
		filenotfound(sev);
		return (NULL);
	}
	for (; *pathlist; pathlist++)
	{
		fpath = _strcat(*pathlist, FSLASH, &(sev->mem));
		fpath = _strcat(fpath, sev->p_input[0], &(sev->mem));
		if (!access(fpath, X_OK))
		{
			sev->error = 0;
			return (fpath);
		}
		if (!access(fpath, F_OK))
		{
			sev->error = 126;
			permdenied(sev);
		}
		else
		{
			if (!sev->error)
			{
				sev->error = 127;
				filenotfound(sev);
			}
		}
	}
	return (NULL);
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
	free_list(&sev->alias, 0);
	free_list(&sev->cmd_q, 0);
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
	add_node(&sev->mem, NULL, evp);
	walker = sev->env;
	for (i = 0; walker; i++)
	{
		evp[i] = (char *)walker->value;
		walker = walker->next;
	}
	evp[i] = NULL;

	return (evp);
}

/**
 * _setenv_helper - set dataptr in node
 * @sev: struct containing shell variables
 * @tofind: string to find
 * @strtoappend: string to append
 *
 * Description: Function parses linked list containing environment variables to
 * to find "tofind." If found, function will append "tofind" with "=" then with
 * "strtoappend" and set the node's dataptr, which "tofind" was found in, as
 * the newly concatenated string. If function fails to find node, then null is
 * returned to the user.
 * Return: 1 if success, 0 if failure
 */
int _setenv_helper(sev_t *sev, char *tofind, char *strtoappend)
{
	list_t *ev = sev->env;
	list_t **mt = &sev->mem;
	char *evstr = NULL;
	unsigned int i = 0;

	for (; ev; ev = ev->next)
	{
		evstr = ev->value;
		for (i = 0; i < _strlen(tofind); i++)
			if (tofind[i] != evstr[i])
				break;
		if (!tofind[i])
		{
			tofind = _strcat(tofind, "=", mt);
			tofind = _strcat(tofind, strtoappend, mt);
			ev->value = _strdup(tofind, mt);
			return (1);
		}
	}
	return (0);
}
