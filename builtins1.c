#include "builtins.h"

/**
 * TODO:
 * 	1. signum > INTMAX..should return 2
 * 	2. Error messages using history
 *
 * 	3. DONT EXIT. RETURN SIGNUM as SEV->ERROR
 */
void exit_sh(sev_t *sev)
{
	char **av = sev->p_input;
	list_t **mt = &(sev->mem);
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
		sigint &= BYTE;
	else
		sigint = 2;		
	free_list(mt, 1);
	_exit(sigint);
}

void _printenv(sev_t *sev)
{
	int i;
	char **ev = sev->env;

	if (ev)
	{
		for (i = 0; ev[i]; i++)
		{
			write(STDOUT_FILENO, ev[i], _strlen(ev[i]));
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
