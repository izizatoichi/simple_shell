#include "builtins.h"

/**
 * TODO: 
 * 	Make linked list of env variables (read_env function)
 *	Change shellvars.h and call read_env in init_sev func in shellhelpers3
 */

/**
 * TODO:
 * 	1. signum > INTMAX..should return 2
 * 	2. Error messages using history
 *
 * 	3. DONT EXIT. SET SEV->ERROR to signum
 * 	4. SET good2go to 0 if exit is called
 * 	1 for illegal exit codes
 */
void exit_sh(sev_t *sev)
{
	char **av = sev->p_input;
	char *signal = "0";
	unsigned long siglong = 0, i, max = (long) INT_MAX;
	int sigint;
	if (av[1])
		signal = av[1];

	for (i = 0; signal[i]; i++)
	{
		if (signal[i] == '-')
		{
			siglong = -1;
			break;
		}

		siglong = (siglong * 10) + signal[i] - '0';
		if (siglong > max)
		{
			siglong = -1;
			break;
		}
	}

	sigint = (int) siglong;
	if (sigint >= 0 && sigint <= INT_MAX)
	{
		sigint &= BYTE;
		sev->error = sigint;
		sev->good2go = 0;
	}
	else
	{
		sigint = 2;
		sev->error = sigint;
		sev->good2go = 1;
	}
}

void _printenv(sev_t *sev)
{
	list_t *ev = sev->env;
	char *s;

	if (ev)
	{
		for (; ev; ev = ev->next)
		{
			s = ev->dataptr;
			write(STDOUT_FILENO, s, _strlen(s));
			write(STDOUT_FILENO, "\n", 1);
		}
	}	
}

/**
 * TODO:
 * 	1. Add more builtin functions
 * 	2. integrate function into main shell
 */
int check_builtin(sev_t *sev)
{	
	int i = 0;
	char *cmd = NULL;
	char **av = sev->p_input;
	
	built_t funclist[] = {{"exit", exit_sh}, 
	  		      {"env", _printenv},
			      {NULL, NULL}};

	if (av && *av)
	{
		cmd = av[0];
		for (i = 0; funclist[i].funcname; i++)
		{
			if (!_strcmp(cmd, funclist[i].funcname))
			{
				funclist[i].func(sev);
				return (1);
			}
		}
	}

	return (0);
}
