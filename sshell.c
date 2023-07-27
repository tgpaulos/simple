#include "sshell.h"

/**
 * main - is a unix command line inpterpreter.
 * @argc: number of arguments
 * @argv: pointer to string of arguments
 * @envp: pointer to environment variable
 *
 * Description: Display a prompt and wait for the user to type
 * -a command. A command line always ends with a new line.
 * -The prompt is dsiplay again each time a command executed.
 * -The command line are simple, no semicolons, pipes,redirectio
 * -The command line are made only of one word. No arguments.
 * -If an executable cannot be found, print an error message and
 *  diplay the prompt again.
 * -Handle errors and end of a file condition (Ctrl + D).
 *
 * Return: 1-success
 */
int main(int argc, char **argv, char **envp)
{
	int status;
	int rstat;

	if (argc < 1)
	{
		return (FAIL);
	}
	else if (argc > 1)
	{
		rstat = ashell(argc, argv, envp, &status);
		if (rstat != 0)
			return (FAIL);
	}
	else if (argc == 1)
	{
		rstat = ishell(argc, argv, envp, &status);
		if (rstat != 0)
			return (SUCC);
	}

	return (SUCC);
}
/**
 * ishell - take input from interactive terminal and execute them
 * @argc: number of arguments
 * @argv: string of arguments
 * @envp: string of environment variable and their values.
 * @status: global variable that holds the value.
 *
 * Return: 0-on success otherwise any number other than zero depending on error
 */
int ishell(int argc, char **argv, char **envp, int *status)
{
	ssize_t wcnt;
	size_t arrptrln;
	char **iaptr, *errptr;
	char **envrn = {NULL};
	char **arg_v = {NULL};
	struct cmd_t cmdtoexe;

	(void)argc;
	if (argv == NULL)
		return (FAIL);
	if (argv[0] == NULL)
		return (FAIL);
	errptr = _cpsasbtoc(argv[0], ERRSTR_0, ':');
	setcmd_t(&cmdtoexe, NULL, arg_v, envrn);
	while (1)
	{
		wcnt = write(1, "$", 2);
		if (wcnt < 0)
			continue;
		iaptr = readcmd(&arrptrln);
		if (iaptr == NULL || iaptr[0] == NULL)
		{
			write(STDOUT_FILENO, errptr, _strlen(errptr));
			continue;
		}
		iaptr[0] = getcmd(iaptr[0], envp);
		if (iaptr[0] == NULL)
		{
			write(STDOUT_FILENO, errptr, _strlen(errptr));
			continue;
		}
		setcmd_t(&cmdtoexe, iaptr[0], iaptr, envp);
		execcmd(&cmdtoexe, status);
		free(iaptr[0]);
		free(iaptr);
	}
	free(errptr);
	return (SUCC);
}
/**
 * ashell - take input from arguments and execute them
 * @argc: number of arguments
 * @argv: string of arguments
 * @envp: environment variables and their value.
 * @status: global variable that hold the status of the program(process)
 *
 * Description: this executes commands from argumuents.
 * Return: 0 on succes any number otherwise.
 */
int ashell(int argc, char **argv, char **envp, int *status)
{
	int i;
	char *errptr;
	char **aptr;
	char **envrn = {NULL};
	char **arg_v = {NULL};
	struct cmd_t cmdtoexe;

	if (argv == NULL)
		return (FAIL);
	errptr = _cpsasbtoc(argv[0], _cpsasbtoc(argv[1], ERRSTR_0, ':'), ':');
	setcmd_t(&cmdtoexe, NULL, arg_v, envrn);
	aptr = (char **)malloc(argc * sizeof(char *));
	if (aptr == NULL)
		return (FAIL);
	for (i = 0; i < argc; i++)
		aptr[i] = argv[i + 1];
	aptr[i] = NULL;
	aptr[0] = getcmd(aptr[0], envp);
	if (aptr[0] == NULL)
	{
		write(STDOUT_FILENO, errptr, _strlen(errptr));
		return (FAIL);
	}
	setcmd_t(&cmdtoexe, aptr[0], aptr, envp);
	execcmd(&cmdtoexe, status);
	free(aptr);
	return (SUCC);
}

/**
 * execcmd - executes the command
 * @exeptr: pointer to the struct of arguments
 * @status: pointer to environment
 *
 * Return: exit on success -1 on failure
 */

int execcmd(struct cmd_t *exeptr, int *status)
{
	pid_t mpid;

	if (exeptr->pthn == NULL || exeptr->argv == NULL)
		return (FAIL);
	if (_streq(exeptr->argv[0], "exit") > 0)
		exit(1);
	mpid = fork();
	if (mpid == -1)
	{
		perror("fork");
		return (FAIL);
	}
	else if (mpid == 0)
	{
		execve(exeptr->pthn, exeptr->argv, exeptr->envp);
		perror("execve");
		_exit(1);
	}
	wait(status);
	return (SUCC);
}
/**
 * readcmd - reads command from std input
 * @arrpln: the length of returned argument array pointer.
 *
 * Return: pointer command read.
 */
char **readcmd(size_t *arrpln)
{
	char buff[1024];
	char **argcmd;
	ssize_t rcnt = 0;
	int tcnt = -1;
	size_t bsize = 1024;
	char *dlmtr_c = " \n";

	argcmd = NULL;
	intlzstr(buff, bsize, '\0');
	while (rcnt == 0 && tcnt < 10)
	{
		rcnt = read(STDIN_FILENO, buff, bsize);
		tcnt++;
	}
	if ((rcnt == 0 && tcnt > 9) || rcnt < 0)
	{
		exit(1);
	}
	argcmd = _tostrarr(buff, dlmtr_c, arrpln);
	if (argcmd == NULL)
		return (NULL);
	if (argcmd[0] == NULL)
		return (NULL);
	return (argcmd);
}
