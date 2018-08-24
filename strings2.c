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
		if (s1[i] == '\0')
			return (0);
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
		if (s[i] == '-')
			negative *= -1;
	for (; s[i] >= '0' && s[i] <= '9'; i++)
		num = (num * 10) + s[i] - '0';
	num *= negative;
	return (num);
}

/**
 * _strcat - conat two strings and adds forward slash between them
 * @s1: string1
 * @s2: string2
 * @mt: memory tracker
 *
 * Description: Function takes two strings and combines them together into
 * a new string. A forward slash is inserted into the new string between the
 * two strings.
 * Return: Concatenated string or NULL
 */
char *_strcat(char *s1, char *s2, list_t **mt)
{
	size_t len1 = 0, len2 = 0, i = 0;
	char *newstring = NULL;

	if (s1)
		len1 = _strlen(s1);
	if (s2)
		len2 = _strlen(s2);

	newstring = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!newstring)
		return (NULL);
	add_node(mt, (void *)newstring);

	reset_buffer(newstring, len1 + len2 + 1);

	for (i = 0; i < len1; i++)
		newstring[i] = s1[i];
	for (; i < len1 + len2; i++)
		newstring[i] = s2[i - len1];

	newstring[i] = '\0';
	return (newstring);
}

/**
 * _itoa - number to string convertor
 * @num: the number of type ssize_t to be converted
 * @mt: ptr to the memory tracker link list
 8 Return: returns the string
 */
char *_itoa(ssize_t num, list_t **mt)
{
	int index = 0, neg = 0;
	char result[MAXNUMLEN];

	if (num == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		if (num < 0)
			neg = 1;
		while (num)
		{
			result[index] = '0' + num % 10;
			num /= 10;
			index++;
		}
		if (neg)
		{
			result[index] = '-';
			index++;
		}
		result[index] = '\0';
		reverse_str(result);
	}
	return (_strdup(result, mt));
}

/**
 * reverse_str - in place string reversal
 * @s: string to be reversed
 * Return: void
 */
char *reverse_str(char *s)
{
	int front = 0, back = _strlen(s) - 1;
	char tmp;

	if (s)
	{
		while (front < back)
		{
			tmp = s[front];
			s[front] = s[back];
			s[back] = tmp;
			front++;
			back--;
		}
	}
	return (s);
}
