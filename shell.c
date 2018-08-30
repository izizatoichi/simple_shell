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
	int exitcode = 0;
	(void)ac;

	initialize_shell_env(&sev, av, ev);

	while (sev.good2go)
	{
		display_prompt(sev);
		getcommand(&sev);
		check_alias(&sev);
		if (!check_builtin(&sev))
			action(&sev);
		display_error(&sev);
	}
	write_log(&sev);
	exitcode = sev.error;
	clean_sev(&sev);
	return (exitcode);
}
