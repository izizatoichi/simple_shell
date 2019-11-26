#ifndef _ERROR_H_
#define _ERROR_H_

#include "../shell.h"

/* error01.c */
char *filenotfound(sev_t *sev);
char *illegalnum(sev_t *sev);
char *permdenied(sev_t *sev);
char *invaliddir(sev_t *sev);
char *invalidalias(sev_t *sev, int reset);

/* error02.c */
char *helpfilenotfound(sev_t *sev);
char *illegaloptions(sev_t *sev);
char *invalidenv(sev_t *sev);

#endif /* _ERROR_H_ */
