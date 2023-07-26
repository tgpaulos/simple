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
 * readpathfcmd - each dir in path for command specified.
 * @cmd: command to look for.
 *
 * Return: full path command
 */

char *readpathfcmd(char *cmd)
{
	char *envt = "/etc/environment";
	char **arrptr, **arrptrpth;
	char *cmd_n;
	char buff[1024];
	char *dlmtr[] = {"\"", ":"};
	ssize_t rcnt;
	int fd, i = 1, bsize;
	size_t arrptrln, arrptrpthln;

	bsize = 1024;
	fd = open(envt, O_RDONLY);
	if (fd == -1)
		return (NULL);
	intlzstr(buff, bsize, '\0');
	rcnt = read(fd, &buff, bsize);
	if (rcnt < 0)
		return (NULL);
	arrptr = _tostrarr(buff, dlmtr[0], &arrptrln);
	arrptrpth = _tostrarr(arrptr[1], dlmtr[1], &arrptrpthln);
	free(arrptr);
	for (i = 0; arrptrpth[i] != NULL && i < (int)arrptrpthln; i++)
	{
		printf("call readdir here\n");
		cmd_n = readdir_fcmd(arrptrpth[i], cmd);
		if (cmd_n != NULL)
		{
			close(fd);
			return (cmd_n);
		}
	}

	close(fd);
	return (NULL);
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
