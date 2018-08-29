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

/**
 * illegaloptions - create error message for cd
 * @sev: struct containing shell variables
 *
 * Description: Create error message using arguments in sev.
 * Return: error message
 */
char *illegaloptions(sev_t *sev)
{
	char *errmsg = NULL;
	char chartoprint[2];

	_chartostr(chartoprint, sev->p_input[1][1]);

	errmsg = _strcat(_getenv("_", sev), COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, _itoa(sev->log_cnt, &sev->mem), &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, sev->input, &sev->mem);
	errmsg = _strcat(errmsg, COLON, &sev->mem);
	errmsg = _strcat(errmsg, SPACE, &sev->mem);
	errmsg = _strcat(errmsg, "Illegal option ", &sev->mem);
	errmsg = _strcat(errmsg, chartoprint, &sev->mem);
	errmsg = _strcat(errmsg, "\n", &sev->mem);
	sev->errmsg = errmsg;

	return (errmsg);
}
