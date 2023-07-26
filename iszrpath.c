#include "sshell.h"
/**
 * _iszrpath - check if the command contain a pathe and separate it.
 * @cmd: string pointer to the command.
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
