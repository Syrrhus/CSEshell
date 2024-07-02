#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>
/* limits.h defines "PATH_MAX". */
#include <limits.h>
#include <ctype.h>
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

#define _GNU_SOURCE

#define SHELL_BUFFERSIZE 256
#define SHELL_INPUT_DELIM " \t\r\n\a"
#define SHELL_OPT_DELIM "-"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

const char *builtin_desc[] = {
    "cd directory_name to change working directory of the shell",
    "help for supported commands",
    "exit to terminate the shell gracefully",
    "usage cd/help/exit",
    "env to list all registered env variables",
    "set env ENV=VALUE to set a new env variable",
    "unsetenv ENV to remove this env from the list of env variables",
};

const char *builtin_commands[] = {
    "cd",      // Changes the current directory of the shell to the specified path. If no path is given, it defaults to the user's home directory.
    "help",    //  List all builtin commands in the shell
    "exit",    // Exits the shell
    "usage",   // Provides a brief usage guide for the shell and its built-in command
    "env",     // Lists all the environment variables currently set in the shell
    "setenv",  // Sets or modifies an environment variable for this shell session
    "unsetenv" // Removes an environment variable from the shell
};
