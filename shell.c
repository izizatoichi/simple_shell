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

	signal(SIGINT, sig_handler);

	while (1)
	{
		PS1;
		cmd = getcommand(&memtracker);
		cv = make_arr_str(cmd, SPACE, &memtracker);
		action(cv, &memtracker);
		free_list(&memtracker, 1);
	}
	return (0);
}
