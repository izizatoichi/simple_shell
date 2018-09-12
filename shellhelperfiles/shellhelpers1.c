#include "../shell.h"

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
	char *buffer = NULL, *tmp = NULL;
	size_t size = 0, len = 0, ws = 0;
	ssize_t numread = -1;

	if (!sev->cmd_q)
	{
		numread = _getline(&buffer, &size, STDIN_FILENO, &sev->mem);
		if (numread == -2 || numread == -1)
		{
			sev->good2go = 0;
			sev->error = sev->olderror;
			if (sev->ia_mode)
				NEWLINE;
		}
		if (numread > 0)
		{
			len = _strlen(buffer);
			if (buffer[len - 1] == '\n')
				buffer[len - 1] = '\0';
		}
		process_input(buffer, sev);
	}
	if (sev->cmd_q)
	{
		tmp = _strdup(sev->cmd_q->value, &sev->mem);
		ws = _strspn(tmp, DELIM);
		if (*(tmp + ws))
			sev->input = tmp + ws;
		else
		{
			sev->input = "";
		}
		delete_node_at_index(&sev->cmd_q, 0);
	}
	else
		sev->input = NULL;
	add_log(sev);
	sev->p_input = make_arr_str(sev->input, DELIM, sev);
	var_expansion(sev);
	return (sev->input);
}

/**
 * make_arr_str - makes an array of strings from an input string
 * @s: input string
 * @sev: shell environment variable struct
 * @delim: const char * used to split each token
 *
 * Description: Function takes in a string and breaks it down into tokens and
 * returns an array of strings.
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
		add_node(&head, NULL, token);
		token = _strtok(NULL, delim);
	}
	if (numnodes)
	{
		reverse_list(&head);
		argv = malloc(sizeof(char *) * (numnodes + 1));
		add_node(&sev->mem, NULL, (void *)argv);
		for (; numnodes >= 0; numnodes--)
			argv[numnodes] = NULL;
		walker = head;
		numnodes = 0;
		while (walker)
		{
			argv[numnodes] = (char *)walker->value;
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
	int status;

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
		{
			wait(&status);
			sev->error = WEXITSTATUS(status);
			if (sev->error)
				sev->errmsg = NULL;
		}
	}
	return (0);
}
