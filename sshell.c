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
	size_t ptrarrln = 0;
	char *error, **argcmd;
	pid_t mpid;
	ssize_t wcnt;
	int succ = 0, fail = -1, status;

	if (argc < 1)
		return (fail);
	error = _cpsasbtoc(argv[0], " No such file or directory\n", ':');
	while (1)
	{
		wcnt = write(1, "$", 2);
		if (wcnt < 0)
			continue;
		argcmd = readcmd(argc, argv, &ptrarrln, envp);
		if (argcmd == NULL || argcmd[0] == NULL)
		{
			write(1, error, _strlen(error));
			continue;
		}
		if (_streq(argcmd[0], "exit") > 0)
			exit(1);
		mpid = fork();
		if (mpid == -1)
		{
			perror("fork");
			return (fail);
		}
		else if (mpid == 0)
		{
			execve(argcmd[0], argcmd, envp);
			perror("execve");
			_exit(1);
		}
		wait(&status);
		free(argcmd[0]);
		free(argcmd);
	}
	free(error);
	return (succ);
}
/**
 * readcmd - reads command from std input
 * @argc: number of arg passed to main
 * @argv: arg passed to the main.
 * @ptrarrln: the length of returned argument array pointer.
 * @envp: pointer to environment variable
 *
 * Return: pointer command read .
 */
char **readcmd(int argc, char **argv, size_t *ptrarrln, char *envp[])
{
	char buff[1024];
	char **argcmd, **cmd;
	ssize_t rcnt;
	int iszln = 0;
	size_t bsize = 1024;
	char *dlmtr_c = " \n";

	argcmd = NULL;
	(void)(argc + argv);
	intlzstr(buff, bsize, '\0');
	rcnt = read(0, buff, bsize);
	if (rcnt == -1)
		return (NULL);
	argcmd = _tostrarr(buff, dlmtr_c, ptrarrln);
	if (argcmd == NULL)
		return (NULL);
	if (argcmd[0] == NULL)
		return (NULL);
	if (_streq(argcmd[0], "exit") > 0)
		return (argcmd);
	cmd = iszrpath(argcmd[0], &iszln);
	if (cmd == NULL)
		return (NULL);
	argcmd[0] = _getcmdpath(cmd[0], cmd[1], envp);
	_freearrmem(cmd, iszln);
	free(cmd);
	if (argcmd[0] == NULL)
		return (NULL);
	return (argcmd);
}

/**
 * intlzstr - initalizes the string or arr of chars.
 * @strptr: pointer to the string to be initialized.
 * @strln: size of the array
 * @ch: character to be initalized with
 *
 */

void intlzstr(char *strptr, size_t strln, char ch)
{
	size_t i;

	for (i = 0; i < strln; i++)
		strptr[i] = ch;
}
/**
 * intlzarrptr - initialize array of pointers to NULL
 * @arrptr: pointer to array of pointers
 * @arrptrln: length of the array of pointers.
 *
 * Return: initialized array of pointers.
 */
void intlzarrptr(char **arrptr, size_t arrptrln)
{
	size_t i;

	for (i = 0; i < arrptrln; i++)
		arrptr[i] = NULL;
}
