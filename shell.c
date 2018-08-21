#include "shell.h"

int main(int ac, char **av, char **ev)
{
	char *cmd = NULL;
	char **cv = NULL;
	char **history = NULL;
	int res = 0;
	(void)ac;
	(void)av;
	(void)ev;
	(void)history;

	signal(SIGINT, sig_handler);

	while (1)
	{
		displayprompt();
		cmd = getcommand();
		cv = make_arr_str(cmd, SPACE);
		res = action(cv);
		(void)res;
	}
	return (0);
}
