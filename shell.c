#include "shell.h"

/**
 * main - the shell program entry point
 * @ac: integer number of command line args
 * @av: null term'd array of strings containing arguments
 * @ev: null term'd array of strings containing environment vars
 * Return: integer result. 0 for success, everything else is an error
 */
int main(int ac, char **av, char **ev)
{
	list_t *memtracker = NULL;
	char *cmd = NULL;
	char **cv = NULL;
	char **history = NULL;
	(void)ac;
	(void)av;
	(void)ev;
	(void)history;
	(void)memtracker;

	signal(SIGINT, sig_handler);

	while (1)
	{
		PS1;
		cmd = getcommand();
		cv = make_arr_str(cmd, SPACE);
		action(cv);
	}
	return (0);
}
