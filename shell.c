#include "shell.h"

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