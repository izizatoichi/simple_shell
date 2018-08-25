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

	numread = _getline(&buffer, &size, STDIN_FILENO, &(sev->mem));
	if (numread == -2 || numread == -1)
	{
		sev->good2go = 0;
		NEWLINE;
	}
	if (numread > 0)
	{
		len = _strlen(buffer);
		if (buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';
	}
	sev->input = buffer;
	add_log(sev);
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
	char *fullpath = NULL, **evp;
	int result = 0;

	if (_strlen(sev->input))
		fullpath = pathfinder(sev);
	if (sev->error)
		return (0);
	if (fullpath)
	{
		pid = fork();
		if (pid == -1)
		{
			sev->error = -1;
			sev->errmsg = "Error spawning child process\n";
		}
		else if (pid == 0)
		{
			evp = make_evp_arr(sev);
			result = execve(fullpath, sev->p_input, evp);
			if (result == -1)
				perror("Error");
		}
		else
			wait(NULL);
	}
	else
	{
		sev->error = -1;
		filenotfound(sev);
	}
	return (0);
}
