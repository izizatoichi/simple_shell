#include "log.h"

/**
 * add_log - add input from user to log
 * @sev: ptr to shell environment variable link list
 * Return: 1 for success, 0 for fail
 */
int add_log(sev_t *sev)
{
	if (add_node(&sev->log, NULL, _strdup(sev->input, &sev->mem)))
	{
		sev->log_cnt++;
		return (1);
	}
	return (0);
}

/**
 * write_log - writes the current sessions' log to a file
 * @sev: ptr to the shell environment variable
 * Return: 1 if success, 0 for fail
 */
int write_log(sev_t *sev)
{
	char *fullpath = NULL, *entry = NULL;
	list_t *walker = NULL;
	int fd = 0, len = 0;

	fullpath = _strcat(_getenv("HOME", sev), "/", &sev->mem);
	fullpath = _strcat(fullpath, LOGFILE, &sev->mem);
	fd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		return (0);
	}
	reverse_list(&(sev->log));
	walker = sev->log;
	while (walker)
	{
		entry = walker->value;
		entry = _strcat(entry, "\n", &sev->mem);
		len = _strlen(entry);
		if (write(fd, entry, len) < len)
		{
			close(fd);
			return (0);
		}
		walker = walker->next;
	}
	close(fd);
	return (1);
}

/**
 * get_log_count - reads and gets the log file count
 * @sev: ptr to the shell environment variable struct
 * Return: number of entries in log file, 0 if empty or fail
 */
int get_log_count(sev_t *sev)
{
	char *fullpath = NULL, buffer[MAXBUFREAD];
	int fd = 0;
	size_t size = MAXBUFREAD, lines = 0;
	ssize_t numread = 1, index = 0;

	fullpath = _strcat(_getenv("HOME", sev), "/", &sev->mem);
	fullpath = _strcat(fullpath, LOGFILE, &sev->mem);

	fd = open(fullpath, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	while (numread)
	{
		numread = read(fd, &buffer, size);
		if (numread == -1)
		{
			close(fd);
			return (0);
		}
		for (index = 0; index < numread; index++)
		{
			if (buffer[index] == '\n')
				lines++;
		}
	}
	return (lines % MAXLOGSIZE);
}
