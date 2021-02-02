#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct builtinCommands
{
  char *name;
  int (*function)(char **args);
} builtinCommands;

int changeDirectory(char **args);

int presentWorkingDirectory(char **args);

int exitShell(char **args);

int displayHelp(char **args);
