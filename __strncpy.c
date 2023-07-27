#include "sshell.h"

/**
 * _strncpy - copy a string
 * @dest: first string
 * @src: second value
 * @n: max number of bytes
 * Return: dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int j = 0;

	while (j < n && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}
	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}
	return (dest);
}
