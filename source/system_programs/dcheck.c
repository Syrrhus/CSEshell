#include <stdlib.h>
#include <stdio.h>
int main(){
    //check status
    int status=system("ps -efj | grep dspawn  | grep -Ev 'tty|pts'");
    printf("%d\n", status);

    //redirect output to txt file
    char cmd[] = "ps -efj | grep dspawn | grep -Ev 'tty|pts' > /tmp/dspawn_output.txt";

    //result of export to txt file
    int result = system(cmd);
    //error handling
    if (result == -1) {
        perror("Failed to execute command");
        return 1;
    }
    
    // open txt file in read mode
    FILE *file = fopen("/tmp/dspawn_output.txt", "r");
    //error handling
    if (!file) {
        perror("Failed to open temporary file");
        return 1;
    }
    
    // instantiate count
    int count = 0;
    //choose buffer size
    char line[1024];

    //char *fgets(char *str, int n, FILE *stream), inc count with each line read
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    
    // Close the file
    fclose(file);
    
    // Print the result
    printf("Number of daemon processes: %d\n", count);
    
    // Remove the temporary file
    remove("/tmp/dspawn_output.txt");
    
    return 0;
}