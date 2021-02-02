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

int executePipedCommands(char **firstCommandArgs, char **secondCommandArgs)
{
  int pfd[2];
  pid_t firstPID, secondPID;

  if (pipe(pfd) < 0)
  {
    perror("Error");
    return 0;
  }

  firstPID = fork();
  if (firstPID == 0)
  {
    dup2(pfd[1], STDOUT_FILENO);
    close(pfd[0]);
    if (execvp(firstCommandArgs[0], firstCommandArgs) == -1)
    {
      perror("Error executing");
    }
    exit(EXIT_FAILURE);
  }
  else if (firstPID < 0)
  {
    perror("Error in forking");
    exit(EXIT_FAILURE);
  }

  secondPID = fork();

  if (secondPID == 0)
  {
    dup2(pfd[0], STDIN_FILENO);
    close(pfd[1]);
    if (execvp(secondCommandArgs[0], secondCommandArgs) == -1)
    {
      perror("Error executing");
    }
    exit(EXIT_FAILURE);
  }
  else if (secondPID < 0)
  {
    perror("Error in forking");
    exit(EXIT_FAILURE);
  }

  close(pfd[0]);
  close(pfd[1]);

  int firstStatus, secondStatus;

  do
  {
    waitpid(firstPID, &firstStatus, WUNTRACED);
  } while (!WIFEXITED(firstStatus) && !WIFSIGNALED(firstStatus));

  do
  {
    waitpid(secondPID, &secondStatus, WUNTRACED);
  } while (!WIFEXITED(secondStatus) && !WIFSIGNALED(secondStatus));

  return 1;
}