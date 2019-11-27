

# Mandalorian Simple Shell



### Project details
-----
Welcome to the `Mandalorian Simple Shell` project!! This program is a simple shell that can be compiled and launched from the command line.


### Syntax
-----
When using this shell, the syntax for running any command follows the familiar syntax when running a command in any other shell.


### Builtin Commands
-----
This shell supports a variety of commands:

`alias` - create or list an alias

`cd` - change directory

`env` - list the current environment variables

`exit` - exit the shell

`history` - display the command history for the current shell session

`setenv` - sets an environment variable

`unsetenv` - unsets an environment variable

*Note:* To read the help information and syntax for a particular builtin command, run the following from the shell prompt:
```
MANDALORIAN$ help <builtin command>
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
| builtin01.c | Builtin commands source code #1 |
| builtin02.c | Builtin commands source code #2 |
| builtin.h | Builtin commands header file |
| error01.c | Error message handling source code |
| error.h | Error message handling header file |
| generate-author.sh | Bash script to generate the `AUTHORS` |
| _getline.c | Our script of `getline` |
| linklist01.c | Link lists source code |
| linklist.h | Link lists header file |
| log01.c | Commands log handling source code |
| log.h | Commands log handling header file |
| man_1_simple_shell | Manual page for our simple shell program |
| memo01.c | Memory handling source code |
| memo.h | Memory handling header file |
| README.md | This file that you are reading |
| shell.c | Primary shell source code |
| shell.h | Shell header file |
| shellhelper01.c | Helper functions used in our implementation of shell #1 |
| shellhelper02.c | Helper functions used in our implementation of shell #2 |
| shellhelper03.c | Helper functions used in our implementation of shell #3 |
| shellhelper04.c | Helper functions used in our implementation of shell #4 |
| shellvar.h | Shell environment variable structure definition |
| string01.c | Str function source code #1 |
| string02.c | Str function source code #2 |
| string03.c | Str function source code #3 |
| string.h | Str function header file |

### Authors
-----
[Mohamed Mehdi Bouchoucha](https://github.com/mmbouchoucha)
