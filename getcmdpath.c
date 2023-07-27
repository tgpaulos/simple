#include "sshell.h"
/**
 * _getcmdpath - get a full path for the directory
 * @cmd: command to be found
 * @path: path to search
 * @envp: pointer to environment variable that hold PATH.
 *
 * Return: full path.
 */
char *_getcmdpath(char *cmd, char *path, char *envp[])
{

	char *crntdir[] = { ".", "/bin", NULL};
	char *cmd_n;
	size_t i;

	if (path != NULL)
	{
		cmd_n = readdir_fcmd(path, cmd);
		if (cmd_n != NULL)
			return (cmd_n);
		else
			return (NULL);
	}
	for (i = 0; crntdir[i] != NULL; i++)
	{
		path = crntdir[i];
		cmd_n = readdir_fcmd(path, cmd);
		if (cmd_n != NULL)
			return (cmd_n);
	}
	path = lkpath(envp);
	if (path == NULL)
		return (NULL);
	cmd_n = lkdirfcmd(path, cmd);
	if (cmd_n != NULL)
		return (cmd_n);
	return (NULL);
}
/**
 * lkdirfcmd - search cmd in the dirctories listed in PATH return the dircpath
 * @path: hold the value os the PATH variable
 * @cmd: the command to look for
 *
 * Return: path to cmd or NULL
 */

char *lkdirfcmd(char *path, char *cmd)
{
	char *dirptr;
	char *cmdptr;

	dirptr = strtok(path, ":");
	while (dirptr != NULL)
	{
		cmdptr = readdir_fcmd(dirptr, cmd);
		if (cmdptr != NULL)
			return (cmdptr);
		dirptr = strtok(NULL, ":");
	}
	return (NULL);
}
/**
 * lkpath - search for PATH variable and return its value
 * @envp: pointer to environment variables
 *
 * Return: PATH values
 */

char *lkpath(char *envp[])
{
	int i;
	char *path;

	for (i = 0; envp[i] != NULL; i++)
	{
		path = strtok(envp[i], "=");
		if (path == NULL)
			continue;
		if (_streq(path, "PATH") > 0)
		{
			path = strtok(NULL, "=");
			return (path);
		}
	}
	return (NULL);
}
/**
 * getcmd - each dir in path for command specified.
 * @aptr: command to look for.
 * @envp: pointer to environment variable.
 *
 * Return: full path command
 */

char *getcmd(char *aptr, char **envp)
{
	char **cmd;
	int iszln = 0;

	if (aptr == NULL)
		return (NULL);
	if (_streq(aptr, "exit") > 0)
		exit(1);
	cmd = iszrpath(aptr, &iszln);
	if (cmd == NULL)
		return (NULL);
	aptr = _getcmdpath(cmd[0], cmd[1], envp);
	_freearrmem(cmd, iszln);
	free(cmd);
	if (aptr == NULL)
		return (NULL);
	return (aptr);
}
/**
 * sortpath - sorts directories in icreasing number of forwardslash
 * @path: array of string pointer to directories
 *
 * Return: return the sorted directories.
 */

char **sortpath(char **path)
{
	size_t i, j, k, cntfsh = 0;
	size_t tmpcnt = 0;
	char *temp;

	for (j = 0; path[j] != NULL; j++)
	{
		tmpcnt = cntfsh;
		for (i = j; path[i] != NULL; i++)
		{
			cntfsh = 0;
			for (k = 0; path[i][k] != '\0'; k++)
			{
				if (path[i][k] == '/')
					cntfsh++;
			}
			if (tmpcnt > cntfsh)
			{
				temp = path[i];
				path[i] = path[j];
				path[j] = temp;
			}
		}
	}
	return (path);
}
