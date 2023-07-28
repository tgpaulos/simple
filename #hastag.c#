#include "sshell.h"

/**
 * hashtag - checks for # comments
 * @buff: string to check
 * Return: void
 */

void hashtag(char *buff)
{
	size_t i = 0;

	while (buff[i] != '\0')
	{
		if (buff[i] == '#' && (i == 0 || buff[i - 1] == ' '))
		{
			while (buff[i] != '\n' && buff[i] != '\0')
			{
				buff[i] = ' ';
				i++;
			}
		}
		else
		{
			i++;
		}
	}
}

