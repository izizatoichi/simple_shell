#include "strings.h"

/**
 * _strchr - locates a character in a string
 * @s: input string
 * @c: input character
 * Description: Function takes a character and locates its position in a string
 * Return: Pointer to position in string or 0 if not found
 */
char *_strchr(char *s, char c)
{
	int i = 0, len = 0;

	while (s[i++] != '\0')
		len++;
	i = 0;
	while (i <= len)
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

/**
 * _chartostr - convert a char to a str
 * @s: buffer
 * @c: input char
 * Return: void
 */
void _chartostr(char *s, char c)
{
	s[0] = c;
	s[1] = '\0';
}
