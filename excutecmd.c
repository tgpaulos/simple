#include "sshell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *execute_command -
 *
 *
 */


void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		if (execv(args[0], args) < 0)
		{
			perror("execv");
			exit(EXIT_FAILURE);
		}
	} else
	{
		wait(NULL);
	}
}

