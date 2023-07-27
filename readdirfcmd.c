#include "sshell.h"
/**
 * readdir_fcmd - reads a directory for a command
 * @dirpth: string pointer to directory path.
 * @cmd: string pointer to path.
 *
 * Return: full path of the command.
 */
char *readdir_fcmd(char *dirpth, char *cmd)
{
	DIR *dir;
	char *cmd_n;
	struct dirent *ent;

	dir = opendir(dirpth);
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	while ((ent = readdir(dir)) != NULL)
	{
		if (_streq(ent->d_name, cmd) > 0)
		{
			cmd_n = _cpsasbtoc(dirpth, cmd, '/');
			closedir(dir);
			if (cmd_n == NULL)
				return (NULL);
			return (cmd_n);
		}
	}
	closedir(dir);
	return (NULL);
}
