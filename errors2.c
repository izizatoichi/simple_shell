#include "errors.h"

/**
 * helpfilenotfound - create error message for help
 * @sev: struct containing shell variables
 *
 * Description: Create error message using arguments in sev.
 * Return: error message
 */
char *helpfilenotfound(sev_t *sev)
{
	char *errmsg = NULL;
	char *msg = "-JS: help: no help topics match `";

	errmsg = _strcat(msg, sev->p_input[1], &sev->mem);
	errmsg = _strcat(errmsg, "'.  Try `help help'.\n", &sev->mem);
	sev->errmsg = errmsg;

	return (errmsg);
}
