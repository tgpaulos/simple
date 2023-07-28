#include "sshell.h"
/**
 * _strlen - counts the character in string array
 * @str: pointer to a string
 *
 * Return: strlen- the length of the string array
 */
size_t _strlen(char *str)
{
	size_t i, strlen;

	strlen = 0;
	for (i = 0; str[i] != '\0'; i++)
		strlen++;
	return (strlen);

}
