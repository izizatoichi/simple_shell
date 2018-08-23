#include "builtins.h"

void exit_sh(int signum, list_t **mt)
{
	int byte = 255;

	free_list(mt, 1);

	if (signum >= 0 && signum <= INT_MAX)
		signum &= byte;
	else
		signum = 2;
	
	_exit(signum);
}

int check_builtin(char **av, list_t **mt)
{	
	int i, result, signal = 0;
	char *cmd;
	built_t funclist[] = {{"exit", exit_sh}, {NULL, NULL}};

	if (av)
	{
		cmd = av[0];

		if(av[1])
			signal = atoi(av[1]);

		for (i = 0; funclist[i].funcname; i++)
		{
			if (!_strcmp(cmd, funclist[i].funcname))
			{
				funclist[i].func(signal, mt);
				return (1);
			}
		}
	}

	return (0);
}
