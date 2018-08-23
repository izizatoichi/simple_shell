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
	sev_t sev;
	(void)ac;
	(void)av;

	sev = init_sev(ev);
	signal(SIGINT, sig_handler);

	while (sev.good2go)
	{
		display_prompt(sev);
		getcommand(&sev);
		action(&sev);
	}
	return (0);
}
