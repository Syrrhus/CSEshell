#include "system_program.h"
#include <stdio.h>
#include <string.h>

//set up array of descriptions
int num_builtin_functions()
{
    return sizeof(builtin_commands) / sizeof(char *);
}


void print_description(const char *function){
    //create for loop to input correct desc based on command input
    int found=0; //add this as a flag to see if command is found
    for (int i=0; i<num_builtin_functions();i++){
        if (strcmp(function, builtin_commands[i]) == 0){
            printf("%s\n", builtin_desc[i]);
            found=1;
            break;
        }
    }
    //return error if not found
    if (!found) {
        printf("The command you gave %s is not part of CSEShell's builtin command\n", function);
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
