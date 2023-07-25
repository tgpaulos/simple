#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 *main - entry point
 *read_input - reads input from the user
 *parse_arguments - tokenize the input string into individual arguments
 *                   and store them in the argv
 *execute_command - execute commands
 *
 */

#define BUFFER_SIZE 100
#define MAX_ARGUMENTS 10


void read_input(char *input)
{
	write(STDOUT_FILENO, "SSH$", 4);
	read(STDIN_FILENO, input, BUFFER_SIZE);
	input[strcspn(input, "\n")] = '\0';
}

int parse_arguments(char *input, char **argv)
{

	char *token;

	int argc = 0;

	token = strtok(input, " ");

	while (token != NULL && argc < MAX_ARGUMENTS - 1)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	return (argc);
}

void execute_command(char **argv)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		execv(argv[0], argv);
		perror("Error:");
		exit(EXIT_FAILURE);
	} else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

int main(void)
{
	char input[BUFFER_SIZE];
	char *argv[MAX_ARGUMENTS];
	int argc;

	while (1)
	{
		read_input(input);

		if (strcmp(input, "exit") == 0)
			break;
		argc = parse_arguments(input, argv);

		execute_command(argv);
	}

	return (0);
}
