#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <stdlib.h>
#include "../linklists.h"
#include "../memoryfiles/memory.h"

#define MAXNUMLEN 1024

/* strings1.c */
char *_strdup(char *str, list_t **mt);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
char *_strtok(char *s, const char *delim);
unsigned int _strlen(char *s);

/* strings2.c */
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
char *_strcat(char *s1, char *s2, list_t **mt);
char *_itoa(ssize_t num, list_t **mt);
char *reverse_str(char *s);

/* strings3.c */
char *_strchr(char *s, char c);
void _chartostr(char *s, char c);

#endif /* _STRINGS_H_ */
