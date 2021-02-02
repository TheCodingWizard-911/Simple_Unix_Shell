#include "shell.h"

int main()
{
  char *command, **args;
  int status;

  do
  {
    printf("\n$_> ");
    command = readCommand();
    args = splitCommand(command);
    status = executeCommand(args);

    free(command);
    free(args);
  } while (status);

  return EXIT_SUCCESS;
}