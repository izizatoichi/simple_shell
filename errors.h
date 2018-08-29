#ifndef _ERRORS_H_
#define _ERRORS_H_

#include "shell.h"

/* errors1.c */
char *filenotfound(sev_t *sev);
char *illegalnum(sev_t *sev);
char *permdenied(sev_t *sev);
char *invaliddir(sev_t *sev);
char *invalidalias(sev_t *sev, int reset);

/* errors2.c */
char *helpfilenotfound(sev_t *sev);
char *illegaloptions(sev_t *sev);
char *invalidenv(sev_t *sev);

#endif /* _ERRORS_H_ */
