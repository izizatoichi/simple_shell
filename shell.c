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
	char *input = NULL;
	char **arr_args = NULL;
	char **history = NULL;
	(void)ac;
	(void)av;
	(void)history;

	signal(SIGINT, sig_handler);

	while (1)
	{
		PS1;
		input = getcommand(&memtracker);
		arr_args = make_arr_str(input, SPACE, &memtracker);
		action(arr_args, ev, &memtracker);
	}
	return (0);
}
