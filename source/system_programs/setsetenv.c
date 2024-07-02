#include <stdio.h>
#include <stdlib.h>

int main(char **args) {
  if (args[1] == NULL || args[2] == NULL) {
    fprintf(stderr, "setenv: expected argument\n");
  } else {
    if (setenv(args[1], args[2], 1) != 0) {
      perror("setenv");
    } else {
      printf("PATH set\n");
    }
  }
  return 1;
}
