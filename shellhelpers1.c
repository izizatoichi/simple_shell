#include "shell.h"

/**
 * sig_handler - handles interruption signal
 * @signum: signal num
 *
 * Description: Function takes signal and performs certain task instead of
 * executing original function
 * Return: void
 */
void sig_handler(int signum)
{
	(void) signum;
	PS2;
}

/**
 * display_prompt - displays the prompt if in interactive mode
 * @sev: shell environment variable
 * Return: nothing
 */
void display_prompt(sev_t sev)
{
	if (sev.ia_mode)
		PS1;
}

/**
 * getcommand - gets the command from the user and returns a string
 * @sev: ptr to the shell environmen variable struct
 * Return: char * string output or NULL if no input
 */
char *getcommand(sev_t *sev)
{
	char *buffer = NULL;
	size_t size = 0, len = 0;
	ssize_t numread = -1;

	while (numread == -1)
	{
		numread = _getline(&buffer, &size, STDIN_FILENO, &(sev->mem));
		fflush(stdin);
		if (numread == -2 || numread == -1)
		{
			free_list(&(sev->mem), 1);
			NEWLINE;
			exit(1);
		}
		if (numread > 0)
		{
			len = _strlen(buffer);
			if (buffer[len - 1] == '\n')
				buffer[len - 1] = '\0';
		}
	}
	sev->input = buffer;
	sev->p_input = make_arr_str(sev->input, SPACE, sev);
	return (sev->input = buffer);
}

/**
 * make_arr_str - makes an array of strings from an input string
 * @sev: shell environment variable struct
 * @delim: const char * used to split each token
 * Return: resulting NULL terminated char ** array of strings. Will return
 * NULL if input s is empty.
 */
char **make_arr_str(char *s, const char *delim, sev_t *sev)
{
	char *token = NULL;
	list_t *head = NULL, *walker = NULL;
	int numnodes = 0;
	char **argv = NULL;

	token = _strtok(s, delim);
	while (token)
	{
		numnodes++;
		add_node(&head, token);
		token = _strtok(NULL, delim);
	}
	if (numnodes)
	{
		reverse_list(&head);
		argv = malloc(sizeof(char *) * (numnodes + 1));
		add_node(&(sev->mem), (void *)argv);
		for (; numnodes >= 0; numnodes--)
			argv[numnodes] = NULL;
		walker = head;
		numnodes = 0;
		while (walker)
		{
			argv[numnodes] = (char *)walker->dataptr;
			walker = walker->next;
			numnodes++;
		}
		free_list(&head, 0);
	}
	return (argv);
}

/**
 * action - function use to fork and execute commands entered by the user
 * @sev: ptr to the shell environment variables struct
 * Return: error code from execve.
 */
int action(sev_t *sev)
{
	pid_t pid;
	int result = 0;
	char *fullpath = NULL;

	if (sev->input)
		fullpath = pathfinder(sev);
	else
		return (-1);
	if (fullpath)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			return (-1);
		}
		if (pid == 0)
		{
			result = execve(fullpath, sev->p_input, NULL);
			if (result == -1)
				perror("Error");
		}
		else
			wait(NULL);
	}
	else if (sev->p_input)
		printf("%s: not found\n", sev->p_input[0]);
	return (0);
}
