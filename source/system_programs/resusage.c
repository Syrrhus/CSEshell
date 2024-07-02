#include <sys/resource.h>
#include <stdio.h>

int execute(char **args){
  struct rusage r_usage;
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage: %ld kilobytes\n",r_usage.ru_maxrss);
  getrusage(RUSAGE_CHILDREN, &r_usage);
  printf("  User CPU time used: %ld.%06ld seconds\n", r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec);
  printf("  System CPU time used: %ld.%06ld seconds\n", r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);
  return 0;
}

int main(int argc, char **args)
{
    return execute(args);
}