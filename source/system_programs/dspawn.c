#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

char output_file_path[PATH_MAX];

static int daemon_work()
{
    int num = 0;
    FILE *fptr;
    char *cwd;
    char buffer[1024];
    
    // write PID of daemon in the beginning
    fptr = fopen(output_file_path, "a");
    if (fptr == NULL)
    {
        printf("PID %d Daemon writing line %d to the file.  \n", getpid(), num);
        return EXIT_FAILURE;
    }

    fprintf(fptr, "Daemon process running with PID: %d, PPID: %d, opening logfile with FD %d\n", getpid(), getppid(), fileno(fptr));

    // then write cwd
    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd == NULL)
    {
        printf("PID %d Daemon writing line %d to the file.  \n", getpid(), num);
        perror("getcwd() error");
        return 1;
    }

    fprintf(fptr, "Current working directory: %s\n", cwd);
    fclose(fptr);

    while (1)
    {

        // use appropriate location if you are using MacOS or Linux
        fptr = fopen(output_file_path, "a");

        if (fptr == NULL)
        {
            return EXIT_FAILURE;
        }

        fprintf(fptr, "PID %d Daemon writing line %d to the file.  \n", getpid(), num);
        num++;

        fclose(fptr);

        sleep(10);

        if (num == 10) // we just let this process terminate after 10 counts
            break;
    }

    return EXIT_SUCCESS;
}

int intermediate_process(){
   //step 4
   signal(SIGHUP, SIG_IGN);
   //sigchld 
   //notify the parent process that one of its child processes has changed state (exited or stopped).

   //sighup
   //instruct a process to reload configuration files or to restart after a configuration change.
   //when sess leader terminates, send all process sighup
   
   //step 5:daemon fork; terminates parent process
   pid_t pid2 = fork();
   //step 6
   //u mask sets file mode creation mask
   //determines permissions to newly created files
   //permission 777: read, write, execute(111 111 111) -> convert to binary
   //set to 0 -> all files are world-rw and executable
   umask(0);
   //freopen:change the file associated with a standard text stream (stderr, stdin, or stdout),
   chdir("/");
   //daemon process
   if (pid2==0){
        //step 6
        //u mask sets file mode creation mask
        //determines permissions to newly created files
        //permission 777: read, write, execute(111 111 111) -> convert to binary
        //set to 0 -> all files are world-rw and executable
        umask(0);
        //freopen:change the file associated with a standard text stream (stderr, stdin, or stdout),
        chdir("/");
        /* Close all open file descriptors */
        int x;
        int fd0, fd1, fd2; 
        for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
        {
            close (x);
        }

        /*
        * Attach file descriptors 0, 1, and 2 to /dev/null. */
        fd0 = open("/dev/null", O_RDWR);
        fd1 = dup(0);
        fd2 = dup(0);
        int result=daemon_work();
            if (result !=EXIT_SUCCESS){
                fprintf(stderr, "Daemon work failed");
                return 1;
            }
            exit(0);
        } else {
            exit(0);
        }
}

int main(){
    // in main() of dspawn.c 

    // Setup path
    if (getcwd(output_file_path, sizeof(output_file_path)) == NULL)
    {
        perror("getcwd() error, exiting now.");
        return 1;
    }
    strcat(output_file_path, "/dspawn.log");
    printf("%s\n", output_file_path);

    //step 1: first fork, parent and childfork() is so that dspawn returns immediately to cseshell and our shell does not wait for the daemon to exit.
   pid_t pid = fork();
   if (pid == 0){
       printf("Child process with pid %d, pgid %d, session id: %d\n", getpid(), getpgid(getpid()), getsid(getpid()));
       //creates new session
       //step 3:tep 3: setsid
// The child (intermediate process) process is by default not a process group leader. It calls setsid() to be the session leader and loses controlling TTY (terminal).
       setsid(); // child tries setsid
       //pgid is process group leader but not sess leader
   }
   else{
       setsid(); // parent tries setsid
       wait(NULL);
       intermediate_process();
   }
   return 0;
}

