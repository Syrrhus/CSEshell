// This program will list all the environment variables available to it at runtime
#include <stdio.h>
#include <string.h>

// Declaration of the external variable 'environ'
// environ is actually defined in the C standard library
extern char **environ; 
int execute(char **args){
   if (strcmp(args[0], "./env") == 0) {
        char **env = environ; // Pointer to the array of environment strings
        
        while (*env) { // Loop until NULL pointer is encountered
            printf("%s\n", *env); // Print the current environment variable
            env++; // Move to the next environment variable
        }
        
        return 0;
   }
}

int main(int argc, char **args)
{
    return execute(args);
}