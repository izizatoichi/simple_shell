#include "shell.h"
/**
 * init_sev - initialzies the shell environment variables
 * @ev: double ptr to the os environment variables
 * Return: the initialized values of type sev_t
 */
sev_t init_sev(char **ev)
{
	sev_t init;
	(void)ev;

	init.good2go = 1;
	init.ia_mode = 1;
	init.log = NULL;
	init.log_cnt = 0;
	init.mem = NULL;
	init.env = ev;
	init.input = NULL;
	init.p_input = NULL;
	init.error = 0;
	init.errmsg = NULL;

	return (init);
}
