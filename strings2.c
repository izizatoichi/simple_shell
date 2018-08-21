#include "strings.h"

/**
 * _strcmp - compares string1 and string 2
 * @s1: string 1
 * @s2: string 2
 *
 * Description: Function takes two strings, s1 and s2, and compares to see if
 * they are equal
 * Return: 0 if equal or difference between s1 and s2
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0')
			return (0);
	}

	return (s1[i] - s2[i]);
}

/**
 * _atoi - converts string to integer
 * @s: string to be converted
 * Description: Finds integers in a string and returns it as an int
 * Return: int
 */
int _atoi(char *s)
{

	int negative = 1, i = 0;
	unsigned int num = 0;

	for (; (s[i] < '0' || s[i] > '9') && s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			negative *= -1;
	}

	for (; s[i] >= '0' && s[i] <= '9'; i++)
	{
		num = (num * 10) + s[i] - '0';
	}

		num *= negative;

	return (num);
}
