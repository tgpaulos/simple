#include "sshell.h"

/**
 *_strlen- This program returns the length of a string
 *@s: string
 *Return:length
 */

int _strlen(char *s)
{
	int ln = 0;

	while (*s != '\0')
	{
		ln++;
		s++;
	}

	return (ln);
}
