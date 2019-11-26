#include "../shell.h"

/* shellhelper01.c */
void sig_hand(int signum);
void display_prompt(sev_t sev);
char *getcommand(sev_t *sev);
char **make_arr_str(char *s, const char *delim, sev_t *sev);
int action(sev_t *sev);

/* shellhelper02.c */
char *_getenv(char *envar, sev_t *sev);
char *pathfinder(sev_t *sev);
void clean_sev(sev_t *sev);
char **make_evp_arr(sev_t *sev);
int _setenv_helper(sev_t *sev, char *tofind, char *cwd);

/* shellhelper03.c */
sev_t *initialize_shell_env(sev_t *sev, char **av, char **ev);
list_t *read_env(sev_t *sev, char **ev);
void display_error(sev_t *sev);
void var_expansion(sev_t *sev);
int print_alias_val(sev_t *sev, char *key, char *value, int flag);

/* shellhelper04.c */
void process_input(char *cmd, sev_t *sev);
void display_banner(int ia_mode);
void check_alias(sev_t *sev);
