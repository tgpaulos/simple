#include "sshell.h"
/**
 * _tostrarr - arrange string buff into arguments
 * @buff: buffer holding the strings of arguments
 * @dlmtr: hold the delimiter string
 * @arrpln: variable to hold the arr ptr length
 * Return: pointer to array of strings.
 */
char **_tostrarr(char *buff, char *dlmtr, size_t *arrpln)
{
	size_t j,  arrptrln;
	char **arrptr;

	j = 1;
	arrptrln = 32;
	arrptr = (char **)malloc((arrptrln + 1) * sizeof(char *));
	if (arrptr == NULL)
		return (NULL);
	arrptr[0] = strtok(buff, dlmtr);
	if (arrptr[0] == NULL)
		return (NULL);
	while ((arrptr[j] = strtok(NULL, dlmtr)) != NULL)
	{
		if (j  >=  arrptrln)
		{
			arrptr = incrarrptrmem(arrptr, &arrptrln);
			if (arrptr == NULL)
				return (NULL);
		}
		j++;
		arrptr[j] = NULL;
	}
	*arrpln = j;
	return (arrptr);
}
/**
 * _chkfordlmtr - check a given character  for delimiter characters
 * @chr: hold the character to becheked
 * @dlmtr: array of delimeter values
 *
 * Return: -1 on failure; index of delimiter on success
 */
int _chkfordlmtr(char chr, char *dlmtr)
{
	int i;

	for (i = 0; dlmtr[i] != '\0'; i++)
	{
		if (chr == dlmtr[i])
			return (1);
	}
	return (-1);
}
/**
 * _freearrmem - free the array of memory used.
 * @ptr: pointer to memory.
 * @ptrln: length of the memory.
 *
 */
void _freearrmem(char **ptr, size_t ptrln)
{
	size_t  i;

	if (ptrln != 0)
	{
		for (i = 0; i < ptrln; i++)
		{
			if (ptr[i] != NULL)
				free(ptr[i]);
		}
	}
}
/**
 * _freemem - free a char array of memory used
 * @ptr: pointer to char of array
 */
void _freemem(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
/**
 * _lktostr - finds str in another str
 * @strs: soucre string where we look
 * @strf: the string to be found
 *
 * Return: 1-succ -1-fail.
 */

int _lktostr(char *strs, char *strf)
{
	size_t i, j;
	int fail = -1;
	int succ = 1;

	for (i = 0; strs[i] != '\0'; i++)
	{
		if (strs[i] == strf[0])
		{
			while (strf[j] != '\0' && strs[i + j] != strf[j])
				j++;
			if ((size_t)_strlen(strf) == j)
				return (succ);
		}
	}
	return (fail);
}
