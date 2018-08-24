#include "builtins.h"

/**
 * exit_sh - terminate shell
 * @sev: struct containing shell variables
 *
 * Description: Function causes shell to exit normally
 * Return: void
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
		if (signal[i] == '-' || (signal[i] < '0' || signal[i] > '9'))
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

/**
 * _printenv - print environment variables
 * @sev: struct containing shell variables
 *
 * Description: Function prints all environment variables
 * Return: void
 */
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
 * check_builtin - call builtin function
 * @sev: struct containing shell variables
 *
 * Description: Function checks if builtin function exists. If it does, the
 * builtin function will be executed.
 * Return: 1 for success; 0 for failure
 */
int check_builtin(sev_t *sev)
{
	int i = 0;
	char *cmd = NULL;
	char **av = sev->p_input;

	built_t funclist[] = {
		{"exit", exit_sh},
		{"env", _printenv},
		{NULL, NULL}
	};

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
