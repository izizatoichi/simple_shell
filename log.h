#ifndef _LOG_H_
#define _LOG_H_

#include "shell.h"

#define LOGFILE ".simple_shell_history"

/* log1.c */
int add_log(sev_t *sev);
int write_log(sev_t *sev);

#endif /* _LOG_H_ */
