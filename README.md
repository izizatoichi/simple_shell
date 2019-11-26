

# Mandalorian Simple Shell



### Project details
-----
Welcome to the `Mandalorian Simple Shell` project! This program is a simple shell that can be compiled and launched from the command line. It contains the most basic features and functions found in the various shell programs.


Note: You can also run this shell in non-interactive mode, by simply piping your desired commands into the shell executable.

### Syntax
-----
When using this shell, the syntax for running any command follows the familiar syntax when running a command in any other shell.


### Builtin Commands
-----
This shell supports a variety of builtin commands:

`alias` - create or list an alias

`cd` - change directory

`env` - list the current environment variables

`exit` - exit the shell

`help` - display help for a builtin command

`history` - display the command history for the current shell session

`setenv` - sets an environment variable

`unsetenv` - unsets an environment variable

*Note:* To read the help information and syntax for a particular builtin command, run the following from the shell prompt:
```
JS$ help <builtin command>
```

### Compilation
-----
Files are compiled this way:
```
$ make all
```

### Files
-----
Brief description of every file in this repository. Subject to change.

| File Name | Description |
| --- | --- |
| AUTHORS | Text file containing the contributing authors |
| builtins1.c | Builtin commands source code #1 |
| builtins2.c | Builtin commands source code #2 |
| builtins.h | Builtin commands header file |
| errors1.c | Error message handling source code |
| errors.h | Error message handling header file |
| generate-authors.sh | Bash script to generate the `AUTHORS` |
| _getline.c | Our implementation of `getline` |
| help_alias | Help file for the `alias` builtin command |
| help_cd | Help file for the `cd` builtin command |
| help_env | Help file for the `env` builtin command |
| help_exit | Help file for the `exit` builtin command |
| help_help | Help file for the `help` builtin command |
| help_history | Help file for the `history` builtin command |
| help_setenv | Help file for the `setenv` builtin command |
| help_unsetenv | Help file for the `unsetenv` builtin command |
| linklists1.c | Link lists source code |
| linklists.h | Link lists header file |
| log1.c | Commands log handling source code |
| log.h | Commands log handling header file |
| man_1_simple_shell | Manual page for our simple shell program |
| memory1.c | Memory handling source code |
| memory.h | Memory handling header file |
| README.md | This file that you are reading |
| shell.c | Primary shell source code |
| shell.h | Shell header file |
| shellhelpers1.c | Helper functions used in our implementation of shell #1 |
| shellhelpers2.c | Helper functions used in our implementation of shell #2 |
| shellhelpers3.c | Helper functions used in our implementation of shell #3 |
| shellhelpers4.c | Helper functions used in our implementation of shell #4 |
| shellvars.h | Shell environment variable structure definition |
| strings1.c | String function source code #1 |
| strings2.c | String function source code #2 |
| strings3.c | String function source code #3 |
| strings.h | String function header file |

### Authors
-----

