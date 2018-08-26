#include "strings.h"

/**
 * _strdup - a function that returns a pointer to a newly allocated space
 * which contains a copy of a given string
 * @str: pointer to an input string
 * @mt: pointer to the memory tracker link list
 * Return: NULL if str is NULL or if fail to allocate memory, otherwise returns
 * pointer to the newly allocated space
 */
char *_strdup(char *str, list_t **mt)
{
	unsigned int len = 0;
	char *s = NULL;

	if (str)
	{
		len = _strlen(str);
		s = malloc(sizeof(char) * (len + 1));
		add_node(mt, NULL, s);
		if (s)
		{
			for (; len; len--)
				s[len] = str[len];
			s[len] = str[len];
		}
	}
	return (s);
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: string s to process
 * @accept: target search characters
 * Return: number of bytes from the initial segment of s that contains accept
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i = 0, j = 0;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; accept[j]; j++)
			if (s[i] == accept[j])
				break;
		if (!accept[j])
			break;
	}
	return (i);
}

/**
 * _strpbrk - searches a string for any of a set of bytes
 * @s: string s to search through
 * @accept: set of bytes to search with
 * Return: pointer to the byte in s that matches one of the bytes in accept;
 * will return NULL if nothing is found
 */
char *_strpbrk(char *s, char *accept)
{
	unsigned int i = 0, j = 0;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; accept[j]; j++)
			if (s[i] == accept[j])
				return (s + i);
	}
	return (NULL);
}

/**
 * _strlen - get the length of the input string
 * @s: input char * string
 * Return: unsigned int length of the input string. 0 for NULL input
 */
unsigned int _strlen(char *s)
{
	unsigned int len = 0;

	if (s && *s)
		for (len = 0; s[len]; len++)
			;
	return (len);
}

/**
 * _strtok - takes in a string and splits it into tokens based on delim
 * @s: input char * string
 * @delim: string of delimiters to split up the input string
 * Return: pointer to the token or NULL if at the end
 */
char *_strtok(char *s, const char *delim)
{
	static char *remainder;
	char *token = NULL;

	if (!s)
	{
		s = remainder;
		if (!s)
			return (NULL);
	}
	s += _strspn(s, (char *)delim);
	if (!*s)
	{
		remainder = NULL;
		return (NULL);
	}
	token = s;
	s = _strpbrk(token, (char *)delim);
	if (s)
	{
		*s = '\0';
		remainder = s + 1;
	}
	else
		remainder = NULL;
	return (token);
}
