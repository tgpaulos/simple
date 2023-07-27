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

/**
 * _strlen - counts the character in string array
 * @str: pointer to a string
 *
 * Return: strlen- the length of the string array
 */
size_t _strlen(char *str)
{
	size_t i, strlen;

	i = 0;
	strlen = 0;
	while (str[i] != '\0')
	{
		strlen++;
		i++;
	}
	return (strlen);

}
