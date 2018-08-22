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
	NEWLINE;
	PS1;
}

/**
 * getcommand - gets the command from the user and returns a string
 * Return: char * string output or NULL if no input
 */
char *getcommand(list_t **mt)
{
	char *buffer = NULL;
	size_t size = 0, len = 0;
	ssize_t numread = -1;

	while (numread == -1)
	{
		numread = _getline(&buffer, &size, STDIN_FILENO, mt);
		fflush(stdin);
		if (numread == -2 || numread == -1)
		{
			freememtracker(mt);
			exit(1);
		}
		if (numread > 0)
		{
			len = _strlen(buffer);
			if (buffer[len - 1] == '\n')
				buffer[len - 1] = '\0';
		}
	}
	return (buffer);
}

/**
 * make_arr_str - makes an array of strings from an input string
 * @s: input char * string
 * @delim: const char * used to split each token
 * Return: resulting NULL terminated char ** array of strings. Will return
 * NULL if input s is empty.
 */
char **make_arr_str(char *s, const char *delim, list_t **mt)
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
		add_node(mt, (void *)argv);
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
		free_list(&head);
	}
	return (argv);
}

/**
 * action - function use to fork and execute commands entered by the user
 * @cv: null termed array of strings that contain the command and flags
 * Return: error code from execve.
 */
int action(char **cv, list_t **mt)
{
	pid_t pid;
	int result = 0;
	(void)mt;

	if (cv)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			return (-1);
		}
		if (pid == 0)
		{
			result = execve(cv[0], cv, NULL);
			if (result == -1)
				perror("Error");
			freememtracker(mt);
			exit(result);
		}
		else
			wait(NULL);
	}
	return (0);
}
