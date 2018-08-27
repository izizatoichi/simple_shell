#include "shell.h"

/**
 * process_input - takes in the user input and parses for multiple commands.
 * Makes a link list and containing all the commands and queues it for
 * for further processing.
 * @cmd: string input from the user
 * @sev: ptr to the shell environment variables
 * Return: Nothing
 */
void process_input(char *cmd, sev_t *sev)
{
	char *token1 = NULL;

	token1 = _strtok(cmd, "\n");
	while (token1)
	{
		add_node(&sev->cmd_q, NULL, _strdup(token1, &sev->mem));
		token1 = _strtok(NULL, "\n");
	}
	reverse_list(&sev->cmd_q);
}
