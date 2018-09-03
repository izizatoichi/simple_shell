#include "shell.h"

/**
 * _getline - gets line from file descriptor
 * @lineptr: pointer to buffer
 * @n: size of buffer
 * @fd: file descriptor
 * @mt: pointer to memory tracker link list
 *
 * Description: Function will read line from file descriptor and put line into
 * buffer. If buffer passed into function is null, a newly allocated buffer
 * will be created for user. Buffer will resize if characters read exceeds
 * buffer size. The "lineptr" is then set as buffer.
 *
 * Return: number of characters read or -1 upon failure
 */
ssize_t _getline(char **lineptr, size_t *n, int fd, list_t **mt)
{
	static char *buf;
	ssize_t char_read = 0, char_to_read = BUF_SIZE / 2;
	ssize_t buf_size = BUF_SIZE, count = 0;

	buf = malloc(buf_size);
	add_node(mt, NULL, buf);

	if (!buf)
		return (-1);

	if (!lineptr || !n)
		return (-1);
	if (*lineptr)
	{
		buf = *lineptr;
		buf_size = *n;
		if (*n == 1)
			char_to_read = 1;
		else
			char_to_read = buf_size / 2;
	}
	reset_buffer(buf, buf_size);
	char_read = read(fd, buf + count, char_to_read);
	if (char_read == -1)
	{
		free(buf);
		return (-1);
	}
	if (char_read == 0)
		return (-2);

	char_read = _strlen(buf);
	count += char_read;
	if (count > 0)
	{
		if (buf[count - 1] == '\n')
			char_read = 0;
	}
	while (char_read)
	{
		if (count >= buf_size - char_to_read)
		{
			buf = (char *)_realloc(buf, buf_size, buf_size * 2, mt);
			buf_size *= 2;
		}
		char_read = read(fd, buf + count, char_to_read);
		if (char_read == -1)
			return (-1);
		char_read = _strlen(buf) - count;
		count += char_read;
		if (buf[count - 1] == '\n')
			break;
	}
	if (buf[count - 1] != '\n')
	{
		*lineptr = buf;
		*n = buf_size;
		write(STDIN_FILENO, "\n", 1);
		return (-3);
	}
	*lineptr = buf;
	*n = buf_size;
	return (count);
}
