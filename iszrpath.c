#include "sshell.h"
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
/**
 * iszrpath - check if the command contain a pathe and separate it.
 * @cmd: string pointer to the command.
 * @iszln: pointer to length ptr array
 *
 * Return: arrof string containing command and path.
 */
char **iszrpath(char *cmd, int *iszln)
{
	char **cmd_n;
	int cmdln = 0, fsh = 0, ln = 3, i;

	if (cmd == NULL)
		return (NULL);
	cmd_n = (char **)malloc(ln * sizeof(char *));
	if (cmd_n == NULL)
		return (NULL);
	cmdln = _strlen(cmd);
	cmd_n[0] = (char *)malloc((cmdln + 1) * sizeof(char));
	if (cmd_n[0] == NULL)
		return (NULL);
	if (_strcp(cmd_n[0], cmd) == 0)
		return (NULL);
	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == '/')
			fsh = i;
	}
	if (fsh == 0)
	{
		*iszln = 1;
		cmd_n[1] = NULL;
		cmd_n[2] = NULL;
		return (cmd_n);
	}
	cmd_n[1] = (char *)malloc((cmdln + 1) * sizeof(char));
	if (cmd_n[1] == NULL)
		return (NULL);
	if (_strcp(cmd_n[1], cmd) == 0)
		return (NULL);
	for (i = fsh + 1; cmd[i] != '\0'; i++)
		cmd_n[0][i - (fsh + 1)] = cmd[i];
	cmd_n[0][i - (fsh + 1)] = '\0';
	for (i = fsh; cmd[i] != '\0'; i++)
		cmd_n[1][i] = '\0';
	*iszln = 2;
	cmd_n[2] = NULL;
	return (cmd_n);
}
/**
 * _strcp - copy string from str_b to str_a
 * @str_a: destination string
 * @str_b: source string
 *
 * Return: number of strings
 */
size_t _strcp(char *str_a, char *str_b)
{
	size_t i;

	if (str_b == NULL || str_a == NULL)
		return (0);
	i = 0;
	while (str_b[i] != '\0')
	{
		str_a[i] = str_b[i];
		i++;
	}
	str_a[i] = '\0';
	return (i - 1);
}
