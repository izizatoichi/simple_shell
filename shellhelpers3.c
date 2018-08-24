#include "shell.h"
/**
 * init_sev - initialzies the shell environment variables
 * @ev: double ptr to the os environment variables
 * Return: the initialized values of type sev_t
 */
sev_t init_sev(void)
{
	sev_t init;

	init.good2go = 1;
	init.ia_mode = 1;
	init.log = NULL;
	init.log_cnt = 0;
	init.mem = NULL;
	init.env = NULL;
	init.input = NULL;
	init.p_input = NULL;
	init.error = 0;
	init.errmsg = NULL;

	return (init);
}

list_t *read_env(sev_t *sev, char **ev)
{
	list_t **mt = &(sev->mem);
	list_t *head = NULL, *new_node = NULL;

	for (; *ev; ev++)
	{
		new_node = add_node(&head, (char *) *ev);
		add_node(mt, (void *) new_node);
	}

	return (head);
}
