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

 * display_banner - displays the shell banner
 * @ia_mode: interactive mode flag
 * Return - nothing
 */
void display_banner(int ia_mode)
{
	if (!ia_mode)
		return;
 	NEWLINE;
	write(STDOUT_FILENO, "_________   _______\n", 20);
	write(STDOUT_FILENO, "\\__    _/  (  ____ \\\n", 21);
	write(STDOUT_FILENO, "   )  (    | (    \\/\n", 21);
	write(STDOUT_FILENO, "   |  |    | (_____ \n", 21);
	write(STDOUT_FILENO, "   |  |    (_____  )\n", 21);
	write(STDOUT_FILENO, "   |  |          ) |\n", 21);
	write(STDOUT_FILENO, "|\\_)  )    /\\____) |\n", 21);
	write(STDOUT_FILENO, "(____/     \\_______)\n", 21);
	NEWLINE;
	NEWLINE;
	write(STDOUT_FILENO, " _______           _______  _        _\n", 39);
	write(1, "(  ____ \\|\\     /|(  ____ \\( \\      ( \\\n", 40);
	write(1, "| (    \\/| )   ( || (    \\/| (      | (\n", 40);
	write(1, "| (_____ | (___) || (__    | |      | |\n", 40);
	write(1, "(_____  )|  ___  ||  __)   | |      | |\n", 40);
	write(1, "      ) || (   ) || (      | |      | |\n", 40);
	write(1, "/\\____) || )   ( || (____/\\| (____/\\| (____/\\\n", 46);
	write(1, "\\_______)|/     \\|(_______/(_______/(_______/\n", 46);
  NEWLINE;
	write(STDOUT_FILENO, "AUTHORS:\n", 9);
	write(STDOUT_FILENO, "\tStephen Chu <stephen.chu530@gmail.com>", 39);
	NEWLINE;
	write(STDOUT_FILENO, "\tJian Huang <jian.huang.8581@gmail.com>", 39);
	NEWLINE;
	write(STDOUT_FILENO, "***********************************\n", 36);
	write(STDOUT_FILENO, " WELCOME TO JIAN'S & STEVE'S SHELL\n", 35);
	write(STDOUT_FILENO, "***********************************\n", 36);
  NEWLINE;
}
