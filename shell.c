#include "sshell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/*ssize_t _getline(char **lineptr, size_t *n, FILE *stream);*/

#define MAX_ARGS 100

/**
 * readCommand - Reads the user command from stdin
 *               and tokenizes it into arguments.
 * @argv:An array to store the command-line arguments
 * @read: read the user input from the standard input (stdin)
 * and tokenize it into command-line arguments.
 */
void readCommand(char **argv, ssize_t *read)
{
	char *line = NULL;
	size_t len = 0;
	int i;

	*read = getline(&line, &len, stdin);
	if (*read == -1)
	{
		perror("getline");
		exit(1);
	}

	argv[0] = strtok(line, " \n");
	for (i = 1; i < MAX_ARGS; i++)
	{
		argv[i] = strtok(NULL, " \n");
		if (argv[i] == NULL)
		{
			break;
		}
	}
}

/**
 * executeCommand - Executes the command using execve.
 * @argv:An array to store the command-line arguments
 */

void executeCommand(char **argv)
{
	/*extern char **environ;*/

	if (execve(argv[0], argv, environ) == -1)
	{
		perror("Error:");
	}
}
/**
 * runShell - Runs the shell program
 *
 */

void runShell(void)
{
	char *argv[MAX_ARGS];
	ssize_t read;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(1);
		} else if (pid == 0)
		{
			readCommand(argv, &read);
			executeCommand(argv);
		} else
		{
			wait(NULL);
		}
	}
}

/**
 * main : entry point of the program.
 *
 */

/*int main(void)
{
	runShell();
	return (0);
}
*/
