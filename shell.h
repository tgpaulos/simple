#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define BUFFER_SIZE 256
#define PROMPT "$SSH"
#define MAX_ARGUMENTS 100

extern char **environ;
void readCommand(char **argv, ssize_t *read);
void executeCommand(char **argv);
void runShell(void);

#endif                                
