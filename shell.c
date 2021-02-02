#include "shell.h"
#include "builtin.h"

builtinCommands builtins[] = {
    {"cd", changeDirectory},
    {"pwd", presentWorkingDirectory},
    {"exit", exitShell},
    {"help", displayHelp},
};

char *readCommand()
{

  size_t length = 4096;
  char *command = (char *)malloc(length * sizeof(char));
  int charactersRead = getline(&command, &length, stdin);

  return command;
}

char **splitCommand(char *command)
{

  int count = 0, capacity = 64;

  char **tokens = (char **)malloc(capacity * sizeof(char *));
  char *delimiters = " \t\r\n";
  char *token = strtok(command, delimiters);

  while (token != NULL)
  {
    tokens[count] = token;
    count++;

    if (count > capacity)
    {
      capacity = capacity * 2;
      tokens = realloc(tokens, capacity * sizeof(char *));
    }

    token = strtok(NULL, delimiters);
  }
  tokens[count] == NULL;

  return tokens;
}

int executeCommand(char **args)
{
  pid_t pid, wpid;

  int i = 0, status;

  if (args[0] == NULL)
  {
    return 1;
  }

  for (i = 0; i < (sizeof(builtins) / sizeof(builtinCommands)); ++i)
  {

    if (strcmp(args[0], builtins[i].name) == 0)
    {
      return builtins[i].function(args);
    }
  }

  pid = fork();
  if (pid == 0)
  {
    // Child process
    if (execvp(args[0], args) == -1)
    {
      perror("Error executing");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    perror("Error in forking");
    exit(EXIT_FAILURE);
  }
  else
  {
    // Parent process
    do
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}