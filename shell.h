#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *readCommand();

char **splitCommand(char *command);

int executeCommand(char **args);

int executePipedCommands(char **firstCommand, char **secondCommand);