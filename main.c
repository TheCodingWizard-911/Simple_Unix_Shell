#include "shell.h"

int main()
{
  char *command, **args;
  int status;

  do
  {
    printf("\n$_> ");
    command = readCommand();

    if (strstr(command, "|"))
    {

      char *firstCommand = strtok(command, "|");
      char *secondCommand = strtok(NULL, "\t\r\n");

      char **firstCommandArguments = splitCommand(firstCommand);
      char **secondCommandArguments = splitCommand(secondCommand);

      if (firstCommandArguments[0] != NULL && secondCommandArguments[0] != NULL)
      {
        status = executePipedCommands(firstCommandArguments, secondCommandArguments);
      }
    }

    else
    {
      args = splitCommand(command);
      status = executeCommand(args);
    }

    free(command);
    free(args);
  } while (status);

  return EXIT_SUCCESS;
}