#include "builtin.h"

int changeDirectory(char **args)
{
  if (args[1] == NULL)
  {
    perror("Error");
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      perror("Unable to change directory\n");
    }
  }
  return 1;
}

int presentWorkingDirectory(char **args)
{
  char currentDirectory[FILENAME_MAX];
  getcwd(currentDirectory, FILENAME_MAX);
  printf("%s\n", currentDirectory);
  return 1;
}

int exitShell(char **args)
{
  return 0;
}

int displayHelp(char **args)
{
  printf("Builtin commands :\ncd\npwd\nexit\nhelp\n");
  return 1;
}
