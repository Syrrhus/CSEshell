#include <stdio.h>
#include <stdlib.h>

int unsetsetenv(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "unsetenv: expected argument\n");
  } else {
    if (unsetenv(args[1]) != 0) {
      perror("unsetenv");
    }
  }
  return 1;
}
