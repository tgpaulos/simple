#include "sshell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - entry point
 *
 *
 */

int main()
{
	char input[BUFFER_SIZE];
	char *args[BUFFER_SIZE];
	ssize_t read_size;
	int index;
	char *token;

	while (1)
	{
		display_prompt();

		read_size = read(STDIN_FILENO, input, BUFFER_SIZE);
		if (read_size == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if (read_size == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			handle_exit();
		}

		input[read_size - 1] = '\0';

		index = 0;
		token = strtok(input, " ");

		while (token != NULL)
		{
			args[index++] = token;
			token = strtok(NULL, " ");
		}
		args[index] = NULL;

		if (args[0] == NULL)
		{
			continue;
		} else if (_strcmp(args[0], "exit") == 0)
		{
			handle_exit();
		} else if (_strcmp(args[0], "env") == 0)
		{
			handle_env();
		} else
		{
			execute_command(args);
		}
	}

	return 0;
}
