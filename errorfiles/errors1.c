#include "errors.h"

/**
 * filenotfound - constructs the error message for file not found
 * @sev: ptr to the shell environment variable
 * Return: the constructed error message
 */
char *filenotfound(sev_t *sev)
{
	char *errmsg = NULL;

	errmsg = _strcat(sev->arg0, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, sev->input, &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, "not found", &sev->mem);
	errmsg = _strcat(errmsg, "\n", &sev->mem);
	sev->errmsg = errmsg;

	return (errmsg);
}

/**
 * illegalnum - constructs the error message for the illegal exit number
 * @sev: ptr to the shell environment variable
 * Return: the constructed error message
 */
char *illegalnum(sev_t *sev)
{
	char *errmsg = NULL;

	errmsg = _strcat(sev->arg0, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, sev->input, &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, "Illegal number: ", &sev->mem);
	errmsg = _strcat(errmsg, sev->p_input[1], &sev->mem);
	errmsg = _strcat(errmsg, "\n", &sev->mem);
	sev->errmsg = errmsg;

	return (errmsg);
}

/**
 * permdenied - constructs the permission denied message
 * @sev: ptr to the shell environment variable struct
 * Return: the constructed error message
 */
char *permdenied(sev_t *sev)
{
	char *errmsg = NULL;

	errmsg = _strcat(sev->arg0, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, sev->input, &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, "Permission denied", &sev->mem);
	errmsg = _strcat(errmsg, "\n", &sev->mem);
	sev->errmsg = errmsg;

	return (errmsg);
}

/**
 * invaliddir - contructs invalid directory error message
 * @sev: struct containing shell variables
 *
 * Description: Function creates error messages based on arguments based on
 * sev.
 * Return: the constructed error message
 */
char *invaliddir(sev_t *sev)
{
	char *errmsg = NULL;

	errmsg = _strcat(sev->arg0, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, sev->input, &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, "can't cd to ", &sev->mem);
	errmsg = _strcat(errmsg, (sev->p_input)[1], &sev->mem);
	errmsg = _strcat(errmsg, "\n", &sev->mem);
	sev->errmsg = errmsg;

	return (errmsg);
}

/**
 * invalidalias - constructs invalid alias error message
 * @sev: struct containing shell variables
 * @node: index of desired key
 *
 * Description: Function creates error messages based on arguments based on
 * sev.
 * Return: the constructed error message
 */
char *invalidalias(sev_t *sev, int node)
{
	char *errmsg = NULL;
	int i = node;

	errmsg = _strcat("alias: ", (sev->p_input)[i++], &sev->mem);
	errmsg = _strcat(errmsg, " not found", &sev->mem);
	errmsg = _strcat(errmsg, "\n", &sev->mem);
	sev->errmsg = errmsg;

	return (errmsg);
}
