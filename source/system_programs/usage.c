#include "system_program.h"
#include <stdio.h>
#include <string.h>

//set up array of descriptions
const char *builtin_desc[] = {
    "cd directory_name to change working directory of the shell",
    "help for supported commands",
    "exit to terminate the shell gracefully",
    "usage cd/help/exit",
    "env to list all registered env variables",
    "set env ENV=VALUE to set a new env variable",
    "unsetenv ENV to remove this env from the list of env variables",
};

//function to print fstring based on function(args[1])
void print_description(const char *function) {
    if (strcmp(function, "cd") == 0) {
        printf("%s\n", builtin_desc[0]);
    } else if (strcmp(function, "help") == 0) {
        printf("%s\n", builtin_desc[1]);
    } else if (strcmp(function, "exit") == 0) {
        printf("%s\n", builtin_desc[2]);
    } else if (strcmp(function, "usage") == 0) {
        printf("%s\n", builtin_desc[3]);
    } else if (strcmp(function, "env") == 0) {
        printf("%s\n", builtin_desc[4]);
    } else if (strcmp(function, "set") == 0) {
        printf("%s\n", builtin_desc[5]);
    } else if (strcmp(function, "unsetenv") == 0) {
        printf("%s\n", builtin_desc[6]);
    } else {
        printf("The command you gave %s, is not part of CSEShell's builtin command\n", function);
    }
}

int execute(char **args)
{
    //if usage is entered
    //i need to change this aft rc file is added
    if (strcmp(args[0], "./usage") == 0) {
        //missing args[1] -> print how to use usage
        if (args[1] == NULL) {
            printf("Usage: usage <command>\n");
            return 1; //return failure
        }
        else{
            char *function = args[1];
            //call print function
            print_description(function);
            return 0; //return success
        }
    }
}



int main(int argc, char **args)
{   
    return execute(args);
}
