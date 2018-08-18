#include "shell.h"

/**
 * displayprompt - displayers prompt using write
 * @s: char * string representing the prompt
 * Return: nada
 */
void displayprompt(void)
{
	write(STDOUT_FILENO, PS1, _strlen(PS1));
	fflush(stdout);
}

/**
 * getcommand - gets the command from the user and returns a string
 * Return: char * string output or NULL if no input
 */
char *getcommand(void)
{
	char *buffer = NULL;
	size_t size = 0, len = 0;
	ssize_t numread = -1;

	while (numread == -1)
	{
		numread = _getline(&buffer, &size, stdin);
		fflush(stdin);
		if (numread != -1)
		{
			len = _strlen(buffer);
			if (buffer[len - 1] == '\n')
			{
				buffer[len - 1] = '\0';
				numread--;
			}
		}
		else
			numread = -1;
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
char **make_arr_str(char *s, const char *delim)
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

int action(char **cv)
{
	pid_t pid;
	int result = 0;

	if (cv)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			return (1);
		}
		if (pid == 0)
		{
			result = execve(cv[0], cv, NULL);
			free(cv);
			return (result);
		}
		else
			wait(NULL);
		free(cv);
	}
	return (0);
}
