#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int hunger = 0;  
    int alive = 1;   

    printf("Welcome to ShellPet!\n");

    while (alive) {
        printf("\nShellPet is hungry. Feed it by typing 'feed'. Quit with 'quit'.\n");
        printf("Enter your command: ");

        char command[50];
        scanf("%s", command);

        if (strcmp(command, "feed") == 0) {
            hunger = 0;  
            printf("\nShellPet is fed and happy!\n");
        } else if (strcmp(command, "quit") == 0) {
            alive = 0;  
            printf("\nGoodbye! ShellPet is sleeping now.\n");
        } else {
            printf("\nInvalid command. Try again!\n");
        }

        sleep(1);

        hunger++;

    
        if (hunger >= 10) {
            printf("\nShellPet is starving! Please feed it!\n");
        }
    }

    return 0;
}
