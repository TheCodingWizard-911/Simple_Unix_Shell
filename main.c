#include "shell.h"

int main()
{
  char *command, **args;
  int status = 1;

  do
  {
    printf("\n$_> ");
    command = readCommand();
    args = splitCommand(command);

    free(command);
    free(args);
  } while (status);

  return EXIT_SUCCESS;
}