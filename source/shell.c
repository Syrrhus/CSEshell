// Include the shell header file for necessary constants and function declarations
#include "shell.h"

// Helper function to figure out how many builtin commands are supported by the shell
int num_builtin_functions()
{
  return sizeof(builtin_commands) / sizeof(char *);
};

int shell_cd(char **args)
{
  char cwd[1024];
  if (args[1] == NULL)
  {
    fprintf(stderr, "shell: expected argument to \"cd\"\n");
    return 1;
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      perror("shell");
    }
  }
  printf("current:%s\n", getcwd(cwd, sizeof(cwd)));
  return 1;
}
int shell_help(char **args)
{
  for (int i = 0; i < num_builtin_functions(); i++)
  {
    printf("%s\n", builtin_commands[i]);
  }
  return 1;
}
int shell_exit(char **args)
{
  return 0;
}
int shell_usage(char **args)
{
  return 1;
}
int list_env(char **args)
{
  return 1;
}
int set_env_var(char **args)
{
  return 1;
}
int unset_env_var(char **args)
{
  return 1;
}

// Function to read a command from the user input
void read_command(char **cmd)
{
  // Define a character array to store the command line input
  char line[MAX_LINE];
  // Initialize count to keep track of the number of characters read
  int count = 0, i = 0;
  // Array to hold pointers to the parsed command arguments
  char *array[MAX_ARGS], *command_token;

  // Infinite loop to read characters until a newline or maximum line length is reached
  for (;;)
  {
    // Read a single character from standard input
    int current_char = fgetc(stdin);
    // Store the character in the line array and increment count
    line[count++] = (char)current_char;
    // If a newline character is encountered, break out of the loop
    if (current_char == '\n')
      break;
    // If the command exceeds the maximum length, print an error and exit
    if (count >= MAX_LINE)
    {
      printf("Command is too long, unable to process\n");
      exit(1);
    }
  }
  // Null-terminate the command line string
  line[count] = '\0';

  // If only the newline character was entered, return without processing
  if (count == 1)
    return;

  // Use strtok to parse the first token (word) of the command
  command_token = strtok(line, " \n");

  // Continue parsing the line into words and store them in the array
  while (command_token != NULL)
  {
    array[i++] = strdup(command_token);  // Duplicate the token and store it
    command_token = strtok(NULL, " \n"); // Get the next token
  }

  // Copy the parsed command and its parameters to the cmd array
  for (int j = 0; j < i; j++)
  {
    cmd[j] = array[j];
  }
  // Null-terminate the cmd array to mark the end of arguments
  cmd[i] = NULL;
}

// Function to display the shell prompt
void type_prompt()
{
  // Use a static variable to check if this is the first call to the function
  static int first_time = 1;
  if (first_time)
  {
    // Clear the screen on the first call
#ifdef _WIN32
    system("cls"); // Windows command to clear screen
#else
    system("clear"); // UNIX/Linux command to clear screen
#endif
    first_time = 0;
  }
  fflush(stdout); // Flush the output buffer
  printf("$$ ");  // Print the shell prompt
}

// The main function where the shell's execution begins
int main(void)
{
  // Define an array to hold the command and its arguments
  char *cmd[MAX_ARGS];
  int child_status;
  // Formulate the full path of the command to be executed
  char full_path[PATH_MAX];
  char cwd[1024];
  pid_t pid;

  while (1)
  {
    type_prompt();     // Display the prompt
    read_command(cmd); // Read a command from the user

    // skips execution if the command is empty
    if (cmd[0] == NULL)
      continue;

    int builtin = 0;
    // Loop through our command list and check if the commands exist in the builtin command list
    for (int command_index = 0; command_index < num_builtin_functions(); command_index++)
    {
      if (strcmp(cmd[0], builtin_commands[command_index]) == 0) // Assume args[0] contains the first word of the command
      {
        builtin = 1;
        // We will create new process to run the function with the specific command except for builtin commands.
        // These have to be done by the shell process.
        if ((*builtin_command_func[command_index])(cmd))
        {
          continue;
        }
        else
        {
          return 0;
        }
        break;
      }
    }

    if (builtin)
      continue;

    printf("current:%s\n", getcwd(cwd, sizeof(cwd)));

    pid = fork();

    if (pid < 0)
    {
      fprintf(stderr, "Fork has failed. Exiting now");
      return 1;
    }
    else if (pid == 0)
    {
      if (getcwd(cwd, sizeof(cwd)) != NULL)
      {
        snprintf(full_path, sizeof(full_path), "%s/bin/%s", cwd, cmd[0]);
        printf("full path: %s\n", full_path);
        execvp(full_path, cmd);
        // if (execv(full_path, cmd) == -1)
        // {
        //   printf("%d", execv(full_path, cmd));
        //   execvp(full_path, cmd);
        // }

        // If execv returns, command execution has failed
        printf("Command %s not found\n", cmd[0]);
        exit(0);
      }
      else
      {
        printf("Failed to get current working directory.");
        exit(1);
      }
    }
    else
    {
      waitpid(pid, &child_status, WUNTRACED);

      if (WIFEXITED(child_status))
      {
        int child_exit_status = WEXITSTATUS(child_status);
      }
      else
      {
        // If execv returns, command execution has failed
        printf("Command %s not found\n", cmd[0]);
        exit(0);
      }
    }

    // Free the allocated memory for the command arguments before exiting
    for (int i = 0; cmd[i] != NULL; i++)
    {
      free(cmd[i]);
      cmd[i] = NULL; // reset each pointer to NULL after freeing
    }
    memset(cwd, '\0', sizeof(cwd)); // clear the cwd array
  }
  return 0;
}